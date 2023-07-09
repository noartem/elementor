import {declareClass, declareMethod, makeEnv, makeUndefined, realizeMethod,} from "./cpp-generator.mjs";

export class BindingClassGenerator {
    #name = "";
    #methods = {};
    #classConstructor = null;

    constructor(name, data) {
        const {classConstructor, methods} = data;

        this.#name = name;
        this.#methods = methods;
        this.#classConstructor = classConstructor;
    }

    get name() {
        return this.#name;
    }

    get methods() {
        return this.#methods;
    }

    get className() {
        return `N${this.#name}`;
    }

    get declaration() {
        return declareClass(this.className, {
            inherits: {
                public: [`Napi::ObjectWrap<${this.className}>`],
            },
            fields: {
                public: [
                    declareMethod(this.className, [`const Napi::CallbackInfo &info`]),
                    declareMethod("GetClass", [`Napi::Env env`], "Napi::Function", {
                        static: true,
                    }),
                    declareMethod(
                        "getInstance",
                        [`const Napi::CallbackInfo &info`],
                        "Napi::Value",
                    ),
                    ...Object.keys(this.methods).map((e) =>
                        declareMethod(e, [`const Napi::CallbackInfo &info`], `Napi::Value`),
                    ),
                ],
                private: [`std::shared_ptr<${this.name}> instance`],
            },
        });
    }

    get #constructorBodyDefaultRealization() {
        return `
            if (info.Length() == 1 && info[0].IsExternal()) {
                this->instance = *info[0].As<Napi::External<std::shared_ptr<${this.name}>>>().Data();
                return;
            }
    
            this->instance = std::make_shared<${this.name}>();
        `;
    }

    get #constructorBodyByOptionsRealization() {
        if (!this.#classConstructor) {
            return null;
        }

        let result = "";

        const {args = [], body} = this.#classConstructor;

        if (args.length > 0) {
            result += this.#makeArgsCheck(args, {
                errorLabel: this.name,
            });
            result += "\n\n";
        }

        result += body;

        return result;
    }

    get #constructorRealization() {
        const body =
            this.#constructorBodyByOptionsRealization ??
            this.#constructorBodyDefaultRealization;

        return realizeMethod(
            `${this.className}::${this.className}`,
            [`const Napi::CallbackInfo &info`],
            "",
            `
                ${makeEnv};
                ${body}
            `,
            {inherits: `ObjectWrap(info)`},
        );
    }

    get #getClassMethodRealization() {
        const methods = Object.keys(this.methods)
            .concat("getInstance")
            .map(
                (e) =>
                    `${this.className}::InstanceMethod("${e}", &${this.className}::${e})`,
            )
            .join(",\n");
        return realizeMethod(
            `${this.className}::GetClass`,
            [`Napi::Env env`],
            `Napi::Function`,
            `
                return DefineClass(env, "${this.className}", {
                    ${methods}
                });
            `,
        );
    }

    get #getInstanceMethodRealization() {
        return realizeMethod(
            `${this.className}::getInstance`,
            [`const Napi::CallbackInfo &info`],
            `Napi::Value`,
            `
                ${makeEnv};
                return Napi::External<std::shared_ptr<${this.name}>>::New(env, &this->instance).As<Napi::Value>();
            `,
        );
    }

    get #methodsRealizations() {
        let result = [];

        for (const method in this.methods) {
            const {args = [], body} = this.methods[method];

            const argsCheck =
                args.length > 0
                    ? this.#makeArgsCheck(args, {
                        errorLabel: `${this.name} ${method}`,
                        return: makeUndefined,
                    })
                    : "";

            result.push(
                realizeMethod(
                    `${this.className}::${method}`,
                    ["const Napi::CallbackInfo& info"],
                    "Napi::Value",
                    `
                    ${makeEnv};
                    ${argsCheck}
                    ${body}
                    return ${makeUndefined};
                `,
                ),
            );
        }

        return result;
    }

    get realization() {
        const methodsRealizations = [
            this.#constructorRealization,
            this.#getClassMethodRealization,
            this.#getInstanceMethodRealization,
            ...this.#methodsRealizations,
        ];

        return methodsRealizations.join("\n\n");
    }

    #makeArgsCheck(args, options = {}) {
        const makeErrorLabel = options.errorLabel ? `${options.errorLabel}: ` : "";
        const makeErrorLabelLiteralPlus = makeErrorLabel
            ? `"${makeErrorLabel}: " + `
            : "";
        const returnValue = options.return ? ` ${options.return}` : "";
        const makeReturn = `return${returnValue}`;

        let result = "";

        result += `
            if (info.Length() < ${args.length}) {
                Napi::TypeError::New(env, "${makeErrorLabel}Expected >=${args.length} arguments").ThrowAsJavaScriptException();
                ${makeReturn};
            }
        `;

        for (let i = 0; i < args.length; i++) {
            const arg = args[i];
            result += `
            auto _${arg.name} = parse_napi_${arg.type}(env, info[${i}]);
            if (!_${arg.name}.has_value()) {
                Napi::TypeError::New(env, ${makeErrorLabelLiteralPlus}parse_error_to_string(_${arg.name}.error())).ThrowAsJavaScriptException();
                ${makeReturn};
            }
            auto ${arg.name} = _${arg.name}.value();
        `;
        }

        return result;
    }
}

import {declareClass, declareMethod, makeEnv, makeUndefined, realizeMethod,} from "./cpp-generator.mjs";
import {hasReturn, singleLine} from "./cpp-parser.mjs";
import {throwError} from "./napi-helpers.mjs";

const validTypes = ['float', 'string', 'size', 'element']

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
                    declareMethod({
                        name: this.className,
                        args: ["const Napi::CallbackInfo &info"],
                    }),
                    declareMethod({
                        name: "GetClass",
                        args: ["Napi::Env env"],
                        returns: "Napi::Function",
                        isStatic: true,
                    }),
                    declareMethod({
                        name: "getInstance",
                        args: [`const Napi::CallbackInfo &info`],
                        returns: "Napi::Value",
                    }),
                    ...Object.keys(this.methods).map((method) =>
                        declareMethod({
                            name: method,
                            args: [`const Napi::CallbackInfo &info`],
                            returns: `Napi::Value`,
                        }),
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

        return realizeMethod({
            name: `${this.className}::${this.className}`,
            args: [`const Napi::CallbackInfo &info`],
            body: `
                ${makeEnv};
                ${body}
            `,
            inherits: `ObjectWrap(info)`,
        });
    }

    get #getClassMethodRealization() {
        const methods = Object.keys(this.methods)
            .concat("getInstance")
            .map(
                (e) =>
                    `${this.className}::InstanceMethod("${e}", &${this.className}::${e}),`,
            )
            .join("\n");

        return realizeMethod({
            name: `${this.className}::GetClass`,
            args: [`Napi::Env env`],
            returns: `Napi::Function`,
            body: `
                return DefineClass(env, "${this.className}", {
                    ${methods}
                });
            `,
        });
    }

    get #getInstanceMethodRealization() {
        return realizeMethod({
            name: `${this.className}::getInstance`,
            args: [`const Napi::CallbackInfo &info`],
            returns: `Napi::Value`,
            body: `
                ${makeEnv};
                return Napi::External<std::shared_ptr<${this.name}>>::New(env, &this->instance).As<Napi::Value>();
            `,
        });
    }

    get #methodsRealizations() {
        let result = [];

        for (const method in this.methods) {
            const {args = [], body, returns} = this.methods[method];

            const argsCheck =
                args.length > 0
                    ? this.#makeArgsCheck(args, {
                        errorLabel: `${this.name} ${method}`,
                        return: makeUndefined,
                    })
                    : "";

            let methodBodyLines = [];

            methodBodyLines.push(`${makeEnv};`);

            if (args.length > 0) {
                methodBodyLines.push(
                    this.#makeArgsCheck(args, {
                        errorLabel: `${this.name} ${method}`,
                        return: makeUndefined,
                    }),
                );
            }

            if (returns && returns !== "void") {
                if (hasReturn(body)) {
                    methodBodyLines.push(body);
                } else if (singleLine(body)) {
                    if (validTypes.includes(returns)) {
                        methodBodyLines.push(`return to_napi_${returns}(env, ${body});`)
                    } else {
                        methodBodyLines.push(`return ${body};`);
                    }
                } else {
                    methodBodyLines.push(body);
                    methodBodyLines.push(`return ${makeUndefined};`);
                }
            } else {
                methodBodyLines.push(body);
                methodBodyLines.push(`return ${makeUndefined};`);
            }

            const methodBody = methodBodyLines.join("\n");

            result.push(
                realizeMethod({
                    name: `${this.className}::${method}`,
                    args: ["const Napi::CallbackInfo& info"],
                    returns: "Napi::Value",
                    body: methodBody,
                }),
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
        const returnValue = options.return ? ` ${options.return}` : "";
        const makeReturn = `return${returnValue}`;

        let result = "";

        const lengthError = throwError(
            `${makeErrorLabel}Expected >=${args.length} arguments`,
        );

        result += `
            if (info.Length() < ${args.length}) {
                ${lengthError};
                ${makeReturn};
            }
        `;

        for (let i = 0; i < args.length; i++) {
            const arg = args[i];

            if (!validTypes.includes(arg.type) && !(arg.type.startsWith('external<') && arg.type.endsWith('>'))) {
                throw new Error(`Invalid argument type: "${arg.type}"`)
            }

            const parseError = throwError(
                (makeErrorLabel ? `"${makeErrorLabel}" + ` : "") +
                `from_napi_error_to_string(_${arg.name}.error())`,
            );
            result += `
                auto _${arg.name} = from_napi_${arg.type}(env, info[${i}]);
                if (!_${arg.name}.has_value()) {
                    ${parseError};
                    ${makeReturn};
                }
                auto ${arg.name} = _${arg.name}.value();
            `;
        }

        return result;
    }
}

import {throwError} from "./napi-helpers.mjs";
import {hasReturn, isSingleLine} from "./code.mjs";

const validTypes = ["float", "string", "size", "element"];

function makeArgsCheck(args, options = {}) {
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

        if (
            !validTypes.includes(arg.type) &&
            !(arg.type.startsWith("external<") && arg.type.endsWith(">"))
        ) {
            throw new Error(`Invalid argument type: "${arg.type}"`);
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

function makeClassConstructorBody({name}, {args, body}) {
    let result = "";

    if (args.length > 0) {
        result += makeArgsCheck(args, {
            errorLabel: name,
        });
        result += "\n\n";
    }

    if (isSingleLine(body) && !body.endsWith(";")) {
        body = `${body};`;
    }

    result += body;

    return result;
}

function makeClassConstructorBodyDefault({name}) {
    return `
        if (info.Length() == 1 && info[0].IsExternal()) {
            this->instance = *info[0].As<Napi::External<std::shared_ptr<${name}>>>().Data();
            return;
        }

        this->instance = std::make_shared<${name}>();
    `;
}

function makeClassMethodBody(classOptions, {name, args = [], body, returns}) {
    let result = "";

    result += `Napi::Env env = info.Env();\n`;

    if (args.length > 0) {
        result += makeArgsCheck(args, {
            errorLabel: `${classOptions.name} ${name}`,
            return: "env.Undefined()",
        });
        result += "\n\n";
    }

    if (returns && returns !== "void") {
        if (hasReturn(body)) {
            result += `${body}\n`;
        } else if (isSingleLine(body)) {
            if (validTypes.includes(returns)) {
                result += `return to_napi_${returns}(env, ${body});\n`;
            } else {
                result += `return ${body};\n`;
            }
        } else {
            throw new Error(
                `'Invalid class method body in "${classOptions.name}::${name}": Method has returns field, but doesn't returns in body.`,
            );
        }
    } else {
        if (isSingleLine(body) && !body.endsWith(";")) {
            body = `${body};`;
        }

        result += `${body}\n`;
        result += "return env.Undefined();\n";
    }

    return result;
}

function makeClassMethod(classOptions, options) {
    return {
        name: options.name,
        args: [{type: "const Napi::CallbackInfo&", name: "info"}],
        returns: "Napi::Value",
        body: makeClassMethodBody(classOptions, options),
    };
}

function makeClassGetClassMethod(className, {methods}) {
    const methodsKeys = Object.keys(methods).concat("getInstance");
    const methodsExports = methodsKeys
        .map((e) => `${className}::InstanceMethod("${e}", &${className}::${e})`)
        .join(",\n");

    return {
        name: "GetClass",
        args: [{type: "Napi::Env", name: "env"}],
        returns: "Napi::Function",
        isStatic: true,
        body: `
            return DefineClass(env, "${className}", {
                ${methodsExports}
            });
        `,
    };
}

function makeCLassGetInstanceMethod({name}) {
    return {
        name: "getInstance",
        args: [{type: "const Napi::CallbackInfo&", name: "info"}],
        returns: "Napi::Value",
        body: `
            Napi::Env env = info.Env();
            return Napi::External<std::shared_ptr<${name}>>::New(env, &this->instance).As<Napi::Value>();
        `,
    };
}

function makeClass(options) {
    const className = `N${options.name}`;

    const constructorBody = options.classConstructor
        ? makeClassConstructorBody(options, options.classConstructor)
        : makeClassConstructorBodyDefault(options);

    return {
        name: className,
        inherits: [{name: `Napi::ObjectWrap<${className}>`}],
        constructors: [
            {
                args: [{type: `const Napi::CallbackInfo&`, name: "info"}],
                inherits: ["ObjectWrap(info)"],
                body: `
                    Napi::Env env = info.Env();
                    ${constructorBody}
                `,
            },
        ],
        methods: [
            makeClassGetClassMethod(className, options),
            makeCLassGetInstanceMethod(options),
            ...Object.entries(options.methods)
                .map(([name, options]) => ({...options, name}))
                .map((e) => makeClassMethod(options, e)),
        ],
        fields: [
            {
                scope: "private",
                type: `std::shared_ptr<${options.name}>`,
                name: "instance",
            },
        ],
    };
}

function makeInitMethod(classes) {
    return {
        name: "Init",
        args: [
            {type: "Napi::Env", name: "env"},
            {type: "Napi::Object", name: "exports"},
        ],
        returns: `Napi::Object`,
        body: `
            ${classes
            .map(
                ({name}) =>
                    `exports.Set(Napi::String::New(env, "N${name}"), N${name}::GetClass(env));`,
            )
            .join("\n")}
            return exports;
        `,
    };
}

export function generateCpp(classes) {
    classes = Object.entries(classes).map(([name, options]) => ({
        ...options,
        name,
    }));

    return {
        name: "elementor",
        comments: "generated by src/napi/bindings.mjs",
        includes: [
            "library.h",
            "elementor.h",
            "from_napi.h",
            "to_napi.h",
            "napi.h",
            "tl/expected.hpp",
        ],
        beforeDeclaration: `#pragma once`,
        afterRealization: `NODE_API_MODULE(addon, Init)`,
        classes: classes.map(makeClass),
        methods: [makeInitMethod(classes)],
    };
}

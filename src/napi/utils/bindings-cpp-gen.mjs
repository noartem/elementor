import {throwError} from "./napi-helpers.mjs";
import {hasReturn, isSingleLine} from "./code.mjs";
import {toSnakeCase} from "./index.mjs";

function makeArgFromNapiCall({type}) {
    if (typeof type === "string") {
        return `from_napi_${toSnakeCase(type)}`;
    }

    switch (type.type) {
        case "external":
            return `from_napi_external<${type.item}>`;
        default:
            throw new Error(`Unknown arg type ${type.type}`);
    }
}

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

        const name = arg.name;

        const parseError = throwError(
            (makeErrorLabel ? `"${makeErrorLabel}" + ` : "") +
            `from_napi_error_to_string(_${name}.error())`,
        );

        result += `
            auto _${name} = ${makeArgFromNapiCall(arg)}(env, info[${i}]);
            if (!_${name}.has_value()) {
                ${parseError};
                ${makeReturn};
            }
            auto ${name} = _${name}.value();
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

function makeClassConstructorBodyDefault({instanceType}) {
    return `
        if (info.Length() == 1 && info[0].IsExternal()) {
            this->instance = *info[0].As<Napi::External<std::shared_ptr<${instanceType}>>>().Data();
            return;
        }

        this->instance = std::make_shared<${instanceType}>();
    `;
}

function makeClassMethodBodyReturns({body, returns}) {
    if (typeof returns === "string") {
        return `to_napi(env, ${body})`;
    }

    switch (returns.type) {
        case "array":
            return `to_napi_array(env, ${body})`;
        case "enum":
            return `to_napi(env, (int) ${body})`;
        default:
            throw new Error(`Unknown returns type ${returns.type}`);
    }
}

function makeClassMethodBody(classOptions, {name, instanceType, args = [], body, returns}) {
    let result = "";

    result += `Napi::Env env = info.Env();\n`;

    if (args.length > 0) {
        result += makeArgsCheck(args, {
            errorLabel: `${classOptions.name} ${name}`,
            return: "env.Undefined()",
        });
        result += "\n\n";
    }

    if (!body) {
        body = `this->instance->${name}(${args.map((e) => e.name).join(", ")})`;
    }

    if (returns && returns !== "void") {
        if (hasReturn(body)) {
            result += `${body}\n`;
        } else if (isSingleLine(body)) {
            result += `return ${makeClassMethodBodyReturns({body, returns})};\n`;
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

function makeClassGetInstanceMethod({instanceType}) {
    return {
        name: "getInstance",
        args: [{type: "const Napi::CallbackInfo&", name: "info"}],
        returns: "Napi::Value",
        body: `
            Napi::Env env = info.Env();
            return Napi::External<std::shared_ptr<${instanceType}>>::New(env, &this->instance).As<Napi::Value>();
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
            makeClassGetInstanceMethod(options),
            ...Object.entries(options.methods)
                .map(([name, options]) => ({...options, name}))
                .map((e) => makeClassMethod(options, e)),
        ],
        fields: [
            {
                scope: "private",
                type: `std::shared_ptr<${options.instanceType}>`,
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

export function generateBindingsCPP(items) {
    const classes = Object.entries(items)
        .filter(([name, {type}]) => type === "class")
        .map(([name, options]) => ({
            instanceType: name,
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
            {value: "to_napi.h", type: "realization"},
            "napi.h",
            "tl/expected.hpp",
        ],
        beforeDeclaration: `#pragma once`,
        afterRealization: `NODE_API_MODULE(addon, Init)`,
        classes: classes.map(makeClass),
        methods: [makeInitMethod(classes)],
    };
}

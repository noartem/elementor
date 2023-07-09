export const makeEnv = `Napi::Env env = info.Env()`;
export const makeUndefined = `env.Undefined()`;

export function declareMethod(name, args, returns = "", options = {}) {
    let result = "";

    if (options.static) {
        result += "static ";
    }

    if (returns) {
        result += `${returns} `;
    }

    result += name;

    result += "(";
    result += args.join(", ");
    result += ")";

    if (options.inherits) {
        result += ` : ${options.inherits}`;
    }

    return result;
}

export function declareClass(name, props = {}) {
    function makeInherits() {
        let result = "";

        const publicInherits = props.inherits?.public ?? [];
        if (publicInherits.length > 0) {
            result += ` : public ${publicInherits.join(", ")}`;
        }

        const privateInherits = props.inherits?.private ?? [];
        if (privateInherits.length > 0) {
            result += ` : private ${privateInherits.join(", ")}`;
        }

        return result;
    }

    function makeDefinition() {
        let result = "";

        result += "class ";
        result += name;

        const inherits = makeInherits();
        if (inherits.length > 0) {
            result += inherits;
        }

        return result;
    }

    function makeBody() {
        let result = "";

        const publicFields = props.fields?.public ?? [];
        if (publicFields.length > 0) {
            result += `public:\n`;
            for (const publicField of publicFields) {
                result += `\t${publicField};\n`;
            }
        }

        const privateFields = props.fields?.private ?? [];
        if (privateFields.length > 0) {
            result += `private:\n`;
            for (const privateField of privateFields) {
                result += `\t${privateField};\n`;
            }
        }

        return result;
    }

    return `${makeDefinition()} {\n${makeBody()}\n};`;
}

export function realizeMethod(name, args, returns, body, options = {}) {
    const declaration = declareMethod(name, args, returns, options);

    const bodyTrimmed = body
        .trim()
        .split("\n")
        .map((e) => e.trim())
        .map((e) => (e ? `\t${e}` : ""))
        .join("\n");

    return `${declaration} {\n${bodyTrimmed}\n}`;
}

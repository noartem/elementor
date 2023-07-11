import {toLines} from "./cpp-parser.mjs";

export const makeEnv = `Napi::Env env = info.Env()`;
export const makeUndefined = `env.Undefined()`;

export function declareMethod(options) {
    let result = "";

    if (options.isStatic) {
        result += "static ";
    }

    if (options.returns) {
        result += `${options.returns} `;
    }

    result += options.name;

    result += "(";
    result += options.args.join(", ");
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

    function makeFields(type) {
        const fields = props.fields?.[type] ?? [];
        if (fields.length > 0) {
            return `${type}:\n${fields.map((e) => `\t${e};`).join("\n\n")}`;
        }
    }

    function makeBody() {
        let result = [];

        const publicFields = makeFields("public");
        if (publicFields) {
            result.push(publicFields);
        }

        const privateFields = makeFields("private");
        if (privateFields) {
            result.push(privateFields);
        }

        return result.join("\n\n");
    }

    return `${makeDefinition()} {\n${makeBody()}\n};`;
}

function fromLines(value) {
    return value.join("\n");
}

function addSemicolon(value) {
    return value
        .map((e) => e.trim())
        .map(line => {
            if (!line) {
                return ''
            } else if ((["{", "[", "(", ",", ";"].includes(line.at(-1)))) {
                return line
            } else {
                return `${line};`
            }
        });
}

function addDepthTabs(value) {
    let depth = 0;

    const result = [];

    for (const line of value) {
        if (line.length === 0) {
            result.push("");
            continue;
        }

        if (["}", "]", ")"].includes(line.at(0))) {
            depth -= 1;
        }

        const tabs = "\t".repeat(depth);
        result.push(`${tabs}${line}`);

        if (["{", "[", "("].includes(line.at(-1))) {
            depth += 1;
        }
    }

    return result;
}

function removeRedundantEmptyLines(value) {
    const result = []

    let emptyLinesCount = 0

    for (const line of value) {
        if (line) {
            emptyLinesCount = 0
        } else {
            if (emptyLinesCount > 0) {
                continue
            } else {
                emptyLinesCount += 1
            }
        }

        result.push(line)
    }

    return result
}

function addPrefix(prefix) {
    return (value) => {
        return value.map((e) => `${prefix}${e}`);
    };
}

function applyBodyRules(body, rules) {
    return fromLines(
        rules.reduce((acc, rule) => rule(acc) ?? acc, toLines(body)),
    );
}

export function realizeMethod(options) {
    const declaration = declareMethod(options);

    const body = applyBodyRules(options.body, [
        addSemicolon,
        addDepthTabs,
        removeRedundantEmptyLines,
        addPrefix("\t"),
    ]);

    return `${declaration} {\n${body}\n}`;
}

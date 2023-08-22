function makeCommonJSImport({path, items = [], default: importDefault}) {
    const result = [];

    if (items.length > 0) {
        const itemsNames = items
            .map((e) =>
                typeof e === "string"
                    ? e
                    : "alias" in e
                        ? `${e.name} : ${e.alias}`
                        : e.name,
            )
            .join(", ");
        result.push(`const {${itemsNames}} = require("${path}")`);
    }

    if (importDefault) {
        result.push(`const ${importDefault} = require("${path}").default`);
    }

    return result;
}

function makeESMImport({path, items, default: importDefault}) {
    let result = "";

    result += "import ";

    if (items.length > 0) {
        result += "{";
        result += items
            .map((e) =>
                typeof e === "string"
                    ? e
                    : "alias" in e
                        ? `${e.name} as ${e.alias}`
                        : e.name,
            )
            .join(", ");
        result += "}";
    }

    if (importDefault) {
        result += `, ${importDefault}`
    }

    result += ` from "${path}"`

    return result
}

function makeItemInterface({name, fields}) {
    return `interface ${name} {\n${fields.map((e) => `\t${e}`).join("\n")}\n}`;
}

function makeItemType({name, value}) {
    return `type ${name} = ${value}`;
}

function makeItemEnum({name, items}) {
    return `enum ${name} {\n${Object.entries(items).map(([key, value]) => `${key} = ${value}`).join(',\n')}\n}`
}

function makeMethodReturns(value) {
    if (typeof value === 'string') {
        return value
    }

    switch (value.type) {
        case "array":
            return `Array<${value.item}>`;
        case "enum":
            return value.name;
        default:
            throw new Error(`Unknown returns type ${value.type}`);
    }
}

function makeItemClassMethod({
                                 name,
                                 args = [],
                                 returns,
                                 body,
                                 scope = "public",
                                 generics = [],
                             }) {
    let result = "";

    result += `${scope} ${name}`;

    if (generics.length > 0) {
        result += `<${generics
            .map((e) => (typeof e === "string" ? e : `${e.name} = ${e.value}`))
            .join(", ")}>`;
    }

    result += "(";

    if (args.length > 0) {
        result += args
            .map((e) => (typeof e === "string" ? e : `${e.name}: ${e.type}`))
            .join(", ");
    }

    result += ")";

    if (returns) {
        result += `: ${makeMethodReturns(returns)}`;
    }

    result += " {";

    result += body;

    result += "}";

    return result;
}

function makeItemClass({
                           name,
                           classExtends = [],
                           classImplements = [],
                           methods = [],
                           fields = [],
                           after,
                       }) {
    let result = "";

    result += `class ${name}`;

    if (classExtends.length > 0) {
        result += ` extends ${classExtends.join(", ")}`;
    }

    if (classImplements.length > 0) {
        result += ` implements ${classImplements.join(", ")}`;
    }

    result += " {\n";

    result += Object.entries(fields)
        .map(
            (e) =>
                `${e.name}${e.value ? "" : "!"}: ${e.type}${
                    e.value ? ` = ${e.value}` : ""
                }`,
        )
        .join("\n");

    result += "\n\n";

    result += Object.entries(methods)
        .map(([name, options]) => ({...options, name}))
        .map(makeItemClassMethod)
        .join("\n\n");

    if (after) {
        result += after;
    }

    result += "}";

    return result;
}

function makeItemByType({type, ...options}) {
    switch (type) {
        case "interface":
            return makeItemInterface(options);
        case "type":
            return makeItemType(options);
        case "enum":
            return makeItemEnum(options);
        case "class":
            return makeItemClass(options);
    }
}

function makeItem({isExport = false, ...options}) {
    const result = makeItemByType(options);
    if (isExport) {
        return `export ${result}`;
    } else {
        return result;
    }
}

export function generateTS({imports = [], items = [], before, after}) {
    const result = [];

    if (before) {
        result.push(before);
    }

    result.push(...imports
        .map(e => (e.module ?? true) ? makeESMImport(e) : makeCommonJSImport(e)));

    result.push(...items.map(makeItem));

    if (after) {
        result.push(after);
    }

    return result.map((e) => (Array.isArray(e) ? e.join("\n") : e)).join("\n\n");
}

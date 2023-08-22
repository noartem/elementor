export const scopes = ["public", "protected", "private"];

function withSuffix(suffix) {
    return (e) => `${e}${suffix}`;
}

function withPrefix(prefix) {
    return (e) => `${prefix}${e}`;
}

export function generateMethodDeclaration({
                                              name,
                                              args = [],
                                              returns,
                                              isStatic,
                                          }) {
    let result = "";

    if (isStatic) {
        result += "static ";
    }

    if (returns) {
        result += `${returns} `;
    }

    result += name;

    result += "(";
    result += args.map(({type, name}) => `${type} ${name}`).join(", ");
    result += ")";

    return result;
}

export function generateClassDeclaration({
                                             name,
                                             constructors = [],
                                             methods = [],
                                             fields = [],
                                             inherits = [],
                                         }) {
    let result = "";

    result += `class ${name}`;

    if (inherits.length > 0) {
        result += ` : ${inherits
            .map((e) => `${e.scope ?? "public"} ${e.name}`)
            .join(", ")}`;
    }

    result += "{";

    for (const scope of scopes) {
        const scopeLines = [
            ...constructors
                .filter((e) => (e.scope ?? "public") === scope)
                .map((e) => ({...e, name}))
                .map(generateMethodDeclaration)
                .map(withSuffix(";")),
            ...methods
                .filter((e) => (e.scope ?? "public") === scope)
                .map(generateMethodDeclaration)
                .map(withSuffix(";")),
            ...fields
                .filter((e) => (e.scope ?? "public") === scope)
                .map((e) => `${e.type} ${e.name}${e.value ? ` = ${e.value}` : ""}`)
                .map(withSuffix(";")),
        ];
        if (scopeLines.length === 0) {
            continue;
        }

        result += `${scope}:${scopeLines.map(withPrefix("")).join("")}`;
    }

    result += "}";

    return result;
}

export function generateMethodRealization({body, inherits = [], ...options}) {
    let result = "";

    result += generateMethodDeclaration(options);

    if (inherits.length > 0) {
        result += ` : ${inherits.join(", ")}`;
    }

    result += `{${body}}`;

    return result;
}

export function generateClassRealization({
                                             name,
                                             constructors = [],
                                             methods = [],
                                         }) {
    return [
        ...constructors.map((e) => ({...e, name: `${name}::${name}`})),
        ...methods.map((e) => ({
            ...e,
            isStatic: false,
            name: `${name}::${e.name}`,
        })),
    ]
        .map(generateMethodRealization)
        .join("");
}

export function generateCPPRealization(
    name,
    {
        comments,
        includes = [],
        classes = [],
        methods = [],
        beforeRealization,
        afterRealization,
    },
) {
    let result = [];

    result.push(`// ${name}.h`);

    if (comments) {
        result.push(`// ${comments}`);
    }

    if (beforeRealization) {
        result.push(beforeRealization);
    }

    if (includes.length > 0) {
        result.push(
            includes
                .filter((e) => typeof e === "string" || e.type === "realization")
                .map(e => typeof e === "string" ? e : e.value)
                .map((e) => `#include "${e}"`),
        );
    }

    result.push(...classes.map(generateClassRealization));

    result.push(...methods.map(generateMethodRealization));

    if (afterRealization) {
        result.push(afterRealization);
    }

    return result.map((e) => (Array.isArray(e) ? e.join("\n") : e)).join("\n\n");
}

export function generateCPPDeclaration(
    name,
    {
        comments,
        includes = [],
        classes = [],
        methods = [],
        beforeDeclaration,
        afterDeclaration,
    },
) {
    const result = [];

    result.push(`// ${name}.cpp`);

    if (comments) {
        result.push(`// ${comments}`);
    }

    if (beforeDeclaration) {
        result.push(beforeDeclaration);
    }

    includes.unshift(`${name}.h`);
    result.push(
        includes
            .filter((e) => typeof e === "string" || e.type === "declaration")
            .map(e => typeof e === "string" ? e : e.value)
            .map((e) => `#include "${e}"`),
    );

    result.push(...classes.map(generateClassDeclaration).map(withSuffix(";")));

    result.push(...methods.map(generateMethodDeclaration).map(withSuffix(";")));

    if (afterDeclaration) {
        result.push(afterDeclaration);
    }

    return result.map((e) => (Array.isArray(e) ? e.join("\n") : e)).join("\n\n");
}

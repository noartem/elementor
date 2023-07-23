function fixType(value) {
    if (value === "size") {
        return "Size";
    }

    if (value === "element") {
        return "Element";
    }

    if (value === "float") {
        return "number";
    }

    return value;
}

function makeClassMethodDeclaration({name, returns = "void", args = []}) {
    args = args.map((e) => `${e.name}: ${e.type}`).join(", ");
    return `${name}(${args}): ${returns}`;
}

function makeClassMethodBody({...options}) {
    return "";
}

export function generateBindingsTS(classes) {
    classes = Object.entries(classes).map(
        ([name, {methods = {}, ...options}]) => ({
            name,
            className: `N${name}`,
            methods: Object.entries(methods)
                .map(([name, options]) => ({...options, name}))
                .map((e) =>
                    e.args
                        ? {
                            ...e,
                            args: e.args.map((e) => ({...e, type: fixType(e.type)})),
                        }
                        : e,
                )
                .map((e) => (e.returns ? {...e, returns: fixType(e.returns)} : e)),
            ...options,
        }),
    );

    return {
        imports: [
            {
                items: classes.filter((e) => !e.asInterface).map((e) => e.className),
                path: "../build/Release/elementor.node",
            },
        ],
        items: [
            {
                isExport: true,
                type: "interface",
                name: "Size",
                fields: ["width: number", "height: number"],
            },
            ...classes
                .filter((e) => e.asInterface)
                .map((e) => ({
                    type: "interface",
                    name: e.asInterface,
                    fields: e.methods.map(makeClassMethodDeclaration),
                })),
            ...classes
                .filter((e) => !e.asInterface)
                .map((e) => ({
                    type: "class",
                    name: e.name,
                    classExtends: [e.className],
                    methods: Object.fromEntries(
                        e.methods
                            .filter(
                                (e) =>
                                    !(e.name.startsWith("get") && (e.args ?? []).length === 0),
                            )
                            .map((e) => [
                                e.name,
                                {
                                    ...e,
                                    body: e.returns
                                        ? `return super.${e.name}(${(e.args ?? [])
                                            .map((e) => e.name)
                                            .join(", ")})`
                                        : `super.${e.name}(${(e.args ?? [])
                                            .map((e) => e.name)
                                            .join(", ")})\nreturn this`,
                                },
                            ]),
                    ),
                    after: e.tsAdditional,
                })),
            {
                isExport: true,
                type: "type",
                name: "Element",
                value: classes
                    .filter((e) => e.isElement)
                    .map((e) => e.name)
                    .join(" | "),
            },
        ].map((e) => ({...e, isExport: true})),
    };
}

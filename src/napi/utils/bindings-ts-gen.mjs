import {toArray} from "./index.mjs";

function fixType(value) {
    switch (value) {
        case "float":
            return "number";
        default:
            return value;
    }
}

export function generateBindingsTS(items) {
    const classes = Object.entries(items)
        .filter(([name, {type}]) => type === "class")
        .map(([name, {methods = {}, ...options}]) => ({
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
    const enums = Object.entries(items)
        .filter(([name, {type}]) => type === "enum")
        .map(([name, options]) => ({name, ...options}))

    return {
        imports: [
            {
                items: classes.filter((e) => e.exports ?? true).map((e) => e.className),
                path: "../build/Release/elementor.node",
                module: false,
            },
            {
                items: [
                    "Size",
                    "Boundaries",
                    "Position",
                    "ElementRect",
                    "RenderElement",
                    "ClipBehavior",
                    "ApplicationContext",
                    "Canvas",
                    "Element",
                    "Window",
                    "Clipboard",
                ],
                module: true,
                path: "./types",
            },
        ],
        items: [
            ...enums
                .map(({name, items}) => ({
                    type: "enum",
                    isExport: true,
                    name,
                    items,
                })),
            ...classes
                .filter((e) => e.exports ?? true)
                .map((e) => ({
                    type: "class",
                    name: e.name,
                    classExtends: [e.className],
                    classImplements: toArray(e.implements),
                    methods: Object.fromEntries(
                        e.methods
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
                    isExport: true,
                }))],
    };
}

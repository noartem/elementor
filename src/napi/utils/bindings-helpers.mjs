import {merge, upper} from "./index.mjs";

export const Class = {
    type: "class",
}

export const Enum = {
    type: "enum",
}

export function makeEnum(items) {
    if (Array.isArray(items)) {
        items = Object.fromEntries(items.map((e, i) => [e, i]));
    }

    return merge(Enum, {items});
}

export const Element = merge(Class, {
    methods: {
        getSize: {
            args: [
                {name: "ctx", type: "ApplicationContext"},
                {name: "window", type: "Window"},
                {name: "boundaries", type: "Boundaries"},
            ],
            returns: "Size",
        },
        paintBackground: {
            args: [
                {name: "ctx", type: "ApplicationContext"},
                {name: "window", type: "Window"},
                {name: "canvas", type: "Canvas"},
                {name: "rect", type: "ElementRect"},
            ],
        },
        getChildren: {
            args: [
                {name: "ctx", type: "ApplicationContext"},
                {name: "window", type: "Window"},
                {name: "rect", type: "ElementRect"},
            ],
            returns: {type: "array", item: "RenderElement"},
        },
        getClipBehaviour: {
            returns: {type: "enum", name: "ClipBehavior"},
        },
    },
    implements: ["Element"],
});

export const defaultBindings = {
    NativeElement: merge(Element, {
        instanceType: "Element",
        classConstructor: {
            args: [
                {
                    name: "element",
                    type: "element",
                },
            ],
            body: `this->instance = element`,
        },
    }),
};

export const WithChild = field("child", "Element");

export const WithChildren = {
    methods: {
        appendChild: {
            args: [{name: "child", type: "Element"}],
            body: `this->instance->appendChild(child)`,
        },
    },
};

export function getter(name, type) {
    if (name && type === undefined) {
        type = name;
        name = "";
    }

    const getterName = `get${upper(name)}`;
    return {
        methods: {
            [getterName]: {
                returns: type,
                body: `this->instance->${getterName}()`,
            },
        },
    };
}

export function setter(name, type) {
    if (name && type === undefined) {
        type = name;
        name = "";
    }

    const setterName = `set${upper(name)}`;
    const argName = name || "value";
    return {
        methods: {
            [setterName]: {
                args: [{name: argName, type}],
                body: `this->instance->${setterName}(${argName})`,
            },
        },
    };
}

export function field(name, type) {
    return merge(getter(name, type), setter(name, type));
}

export function exports(exports = true) {
    return {exports};
}

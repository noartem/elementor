import {merge, upper} from "./index.mjs";

export const WithChild = {
    methods: {
        setChild: {
            args: [{name: "child", type: "element"}],
            body: `this->instance->setChild(child)`,
        },
    },
};

export const WithChildren = {
    methods: {
        appendChild: {
            args: [{name: "child", type: "element"}],
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
    const argName = name || 'value'
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

export const isElement = {isElement: true}

export function asInterface(name) {
    return {asInterface: name};
}

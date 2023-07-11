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
    const setterName = `set${upper(name)}`;
    return {
        methods: {
            [setterName]: {
                args: [{name, type}],
                body: `this->instance->${setterName}(${name})`,
            },
        },
    };
}

export function field(name, type) {
    return merge(getter(name, type), setter(name, type));
}
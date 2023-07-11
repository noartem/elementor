import {merge} from "./utils/index.mjs";
import * as napi from "./utils/napi-helpers.mjs";
import {field, setter, WithChild, WithChildren} from "./utils/bindings-helpers.mjs";

export default {
    GLPlatform: {
        methods: {
            makeWindow: {
                args: [{name: "size", type: "size"}],
                body: `
                    auto window = this->instance->makeWindow(size);
                    window->setMinSize(size);
                
                    auto windowConstructor = NGLWindow::GetClass(env);
                    auto wrapped = Napi::External < std::shared_ptr < GLWindow >> ::New(env, &window);
                    return windowConstructor.New({wrapped});
                `,
            },
            run: {
                body: `this->instance->run()`,
            },
        },
    },
    GLWindow: merge(
        field("title", "string"),
        field("minSize", "size"),
        field("maxSize", "size"),
        setter("root", "element"),
        {
            classConstructor: {
                args: [{name: "window", type: "external<std::shared_ptr<GLWindow>>"}],
                body: `this->instance = window`,
            },
        },
    ),
    GLClipboard: {
        methods: {
            get: {
                returns: "string",
                body: napi.newString(`this->instance->get()`),
            },
            set: {
                args: [{name: "text", type: "string"}],
                body: `this->instance->set(text)`,
            },
        },
    },
    Padding: merge(WithChild, {
        methods: {
            setPaddings: {
                args: [
                    {name: "top", type: "float"},
                    {name: "right", type: "float"},
                    {
                        name: "bottom",
                        type: "float",
                    },
                    {name: "left", type: "float"},
                ],
                body: `this->instance->setPaddings(top, right, bottom, left)`,
            },
        },
    }),
    Background: merge(WithChild, setter("color", "string")),
    Rounded: merge(WithChild, {
        methods: {
            setRadius: {
                args: [
                    {name: "topLeft", type: "float"},
                    {name: "topRight", type: "float"},
                    {
                        name: "bottomRight",
                        type: "float",
                    },
                    {name: "bottomLeft", type: "float"},
                ],
                body: `this->instance->setRadius(topLeft, topRight, bottomRight, bottomLeft)`,
            },
        },
    }),
    Row: merge(WithChildren, field("spacing", "float")),
    Flex: merge(WithChildren, field("spacing", "float")),
    Flexible: merge(WithChild, field("grow", "float")),
    Width: merge(WithChild, field("width", "float")),
    Center: WithChild,
};

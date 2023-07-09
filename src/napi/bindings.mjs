import {merge} from "./utils/index.mjs";

const WithChild = {
    methods: {
        setChild: {
            args: [{name: "child", type: "element"}],
            body: `this->instance->setChild(child);`,
        },
    }
}

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
                body: `this->instance->run();`,
            },
        },
    },
    GLWindow: {
        classConstructor: {
            args: [{name: "window", type: "external<std::shared_ptr<GLWindow>>"}],
            body: `this->instance = window;`,
        },
        methods: {
            setTitle: {
                args: [{name: "title", type: "string"}],
                body: `this->instance->setTitle(title);`,
            },
            setMinSize: {
                args: [{name: "size", type: "size"}],
                body: `this->instance->setMinSize(size);`,
            },
            setMaxSize: {
                args: [{name: "size", type: "size"}],
                body: `this->instance->setMaxSize(size);`,
            },
            setRoot: {
                args: [{name: "root", type: "element"}],
                body: `this->instance->setRoot(root);`,
            },
        },
    },
    GLClipboard: {
        methods: {
            get: {
                body: `return Napi::String::New(env, this->instance->get());`,
            },
            set: {
                args: [{name: "text", type: "string"}],
                body: `this->instance->set(text);`,
            },
        },
    },
    Padding: merge(WithChild, {
        methods: {
            setPaddings: {
                args: [
                    {name: "top", type: "float"},
                    {name: "right", type: "float"},
                    {name: "bottom", type: "float"},
                    {name: "left", type: "float"},
                ],
                body: `this->instance->setPaddings(top, right, bottom, left);`,
            },
        },
    }),
    Background: merge(WithChild, {
        methods: {
            setColor: {
                args: [{name: "color", type: "string"}],
                body: `this->instance->setColor(color);`,
            },
        },
    }),
    Rounded: merge(WithChild, {
        methods: {
            setRadius: {
                args: [
                    {name: "topLeft", type: "float"},
                    {name: "topRight", type: "float"},
                    {name: "bottomRight", type: "float"},
                    {name: "bottomLeft", type: "float"},
                ],
                body: `this->instance->setRadius(topLeft, topRight, bottomRight, bottomLeft);`,
            }
        }
    })
};

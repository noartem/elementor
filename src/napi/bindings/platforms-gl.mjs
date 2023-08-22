import {merge} from "../utils/index.mjs";
import {Class, exports, field, setter} from "../utils/bindings-helpers.mjs";

export default {
    GLPlatform: merge(Class, {
        methods: {
            makeWindow: {
                args: [{name: "size", type: "Size"}],
                returns: "Window",
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
    }),
    GLWindow: merge(
        Class,
        exports(false),
        field("title", "string"),
        field("minSize", "Size"),
        field("maxSize", "Size"),
        setter("root", "element"),
        {
            classConstructor: {
                args: [
                    {
                        name: "window",
                        type: {type: "external", item: "std::shared_ptr<GLWindow>"},
                    },
                ],
                body: `this->instance = window`,
            },
        },
    ),
    GLClipboard: merge(Class, exports(false), field("string")),
}
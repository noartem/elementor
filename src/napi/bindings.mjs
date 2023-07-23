import {merge} from "./utils/index.mjs";
import {asInterface, field, isElement, setter, WithChild, WithChildren,} from "./utils/bindings-helpers.mjs";

export default {
    GLPlatform: {
        methods: {
            makeWindow: {
                args: [{name: "size", type: "size"}],
                returns: 'Window',
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
        asInterface("Window"),
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
    GLClipboard: merge(asInterface("Clipboard"), field("string")),
    Padding: merge(isElement, WithChild, {
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
        tsAdditional: `
            set(top: number, right?: number, bottom?: number, left?: number) {
                right ??= top
                bottom ??= top
                left ??= right
                return this.setPaddings(top, right, bottom, left)
            }
        `
    }),
    Background: merge(isElement, WithChild, setter("color", "string")),
    Rounded: merge(isElement, WithChild, {
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
        tsAdditional: `
            set(topLeft: number, topRight?: number, bottomRight?: number, bottomLeft?: number) {
                topRight ??= topLeft
                bottomRight ??= topRight
                bottomLeft ??= topLeft
                return this.setRadius(topLeft, topRight, bottomRight, bottomLeft)
            }
        `
    }),
    Row: merge(isElement, WithChildren, field("spacing", "float")),
    Flex: merge(isElement, WithChildren, field("spacing", "float"), {
        tsAdditional: `
            appendFlexible(value: Element) {
                return this.appendChild(new Flexible().setChild(value));
            }
        `,
    }),
    Flexible: merge(isElement, WithChild, field("grow", "float")),
    Width: merge(isElement, WithChild, field("width", "float")),
    Height: merge(isElement, WithChild, field("height", "float")),
    Center: merge(isElement, WithChild),
};

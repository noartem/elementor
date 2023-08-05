import {merge} from "./utils/index.mjs";
import {Element, exports, field, setter, WithChild, WithChildren,} from "./utils/bindings-helpers.mjs";

/** TODO:
 * * Унифицировать from_napi, to_napi -- каждый тип это объект, в котором есть код encode/decode для всех языков
 * * NGLWindow заменить на NWindow
 * * Каждый биндинг в отдельном файле
 * * * Import-export элементов и types.ts в elementor.ts
 * * * Каждый биндинг сам за себе генерирует код
 * * Генерировать все енамы -- смотреть по файлам library/elements/*.h все enum class и парсить их
 * * Разобраться с приведением всех новых типов
 * * * Все которые были (единиый стандарт)
 * * * Енамы
 * * * Массив
 */

const gl = {
    GLPlatform: {
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
    },
    GLWindow: merge(
        exports(false),
        field("title", "string"),
        field("minSize", "Size"),
        field("maxSize", "Size"),
        setter("root", "element"),
        {
            classConstructor: {
                args: [{name: "window", type: "external<std::shared_ptr<GLWindow>>"}],
                body: `this->instance = window`,
            },
        },
    ),
    GLClipboard: merge(
        exports(false),
        field("string")
    ),
}

export default {
    ...gl,
    Padding: merge(Element, WithChild, {
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
        `,
    }),
    Background: merge(Element, WithChild, setter("color", "string")),
    Rounded: merge(Element, WithChild, {
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
        `,
    }),
    Row: merge(Element, WithChildren, field("spacing", "float")),
    Flex: merge(Element, WithChildren, field("spacing", "float"), {
        tsAdditional: `
            appendFlexible(value: Element) {
                return this.appendChild(new Flexible().setChild(value));
            }
        `,
    }),
    Flexible: merge(Element, WithChild, field("grow", "float")),
    Width: merge(Element, WithChild, field("width", "float")),
    Height: merge(Element, WithChild, field("height", "float")),
    Center: merge(Element, WithChild),
    Text: merge(
        Element,
        field("text", "string"),
        setter("fontColor", "string"),
        field("fontSize", "float"),
        field("fontSkew", "float"),
        field("fontScale", "float"),
        field("fontFamily", "string"),
    ),
};

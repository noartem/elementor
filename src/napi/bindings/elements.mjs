import {merge} from "../utils/index.mjs";
import {Element, field, setter, WithChild, WithChildren,} from "../utils/bindings-helpers.mjs";

export default {
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

//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_PADDING_H
#define ELEMENTOR_PADDING_H

#include "Element.h"

namespace elementor {
    struct PaddingsValue {
        float top;
        float right;
        float bottom;
        float left;
    };

    struct PaddingsIntValue {
        int top;
        int right;
        int bottom;
        int left;
    };

    class Padding : public Element, public WithChild {
    public:
        Padding *setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft);

        Padding *setPaddings(float paddingTop, float paddingX, float paddingBottom);

        Padding *setPaddings(float paddingY, float paddingX);

        Padding *setPaddings(float paddings);

        PaddingsValue getPaddings();

        Padding *setChild(Element *child);

        std::shared_ptr <ElementRenderer> render() override;

    private:
        PaddingsValue paddings;
    };

    Padding *padding();

    class PaddingRenderer : public ElementRenderer {
    public:
        PaddingRenderer(ApplicationContext *context, PaddingsValue paddings, Element *child);

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        PaddingsIntValue paddings;
        Element *child;
    };
}


#endif //ELEMENTOR_PADDING_H

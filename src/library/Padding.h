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
        Padding() {};

        Padding(Element *child);

        Padding(float paddings, Element *child);

        Padding(float paddingY, float paddingX, Element *child);

        Padding(float paddingTop, float paddingX, float paddingBottom, Element *child);

        Padding(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft, Element *child);

        void setPaddings(float paddings);

        void setPaddings(float paddingY, float paddingX);

        void setPaddings(float paddingTop, float paddingX, float paddingBottom);

        void setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft);

        std::shared_ptr <ElementRenderer> render() override;

    private:
        PaddingsValue paddings;
    };

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

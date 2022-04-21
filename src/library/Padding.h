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

    class Padding : public Element {
    public:
        Element *child;

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
        PaddingsValue paddings;
        Element *child;

        std::vector <RenderElement> getChildren(RenderSize size) override;
    };
}


#endif //ELEMENTOR_PADDING_H

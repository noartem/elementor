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

    class Padding : public Element, WithChild {
    public:
        Padding *setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft);

        Padding *setPaddings(float paddingTop, float paddingX, float paddingBottom);

        Padding *setPaddings(float paddingY, float paddingX);

        Padding *setPaddings(float paddings);

        PaddingsValue getPaddings();

        int getPaddingTop();

        int getPaddingRight();

        int getPaddingBottom();

        int getPaddingLeft();

        Padding *setChild(Element *child);

        RenderSize getSize(RenderBoundaries boundaries) override;

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        PaddingsValue paddings;
    };

    Padding *padding();
}


#endif //ELEMENTOR_PADDING_H

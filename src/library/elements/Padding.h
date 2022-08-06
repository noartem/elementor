//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_PADDING_H
#define ELEMENTOR_PADDING_H

#include "../Element.h"

namespace elementor::elements {
    struct PaddingsValue {
        float top;
        float right;
        float bottom;
        float left;
    };

    class Padding : public Element, public WithChild {
    public:
        Padding *setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft);

        Padding *setPaddings(float paddingTop, float paddingX, float paddingBottom);

        Padding *setPaddings(float paddingY, float paddingX);

        Padding *setPaddings(float paddings);

        PaddingsValue getPaddings();

        Padding *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

    private:
        PaddingsValue paddings;
    };

    Padding *padding();
}


#endif //ELEMENTOR_PADDING_H

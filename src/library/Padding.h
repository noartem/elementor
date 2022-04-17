//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_PADDING_H
#define ELEMENTOR_PADDING_H

#include "Element.h"

namespace elementor {
    struct PaddingsValue {
        int top;
        int right;
        int bottom;
        int left;
    };

    class Padding : public Element {
    public:
        PaddingsValue paddings;
        Element *child;

        std::unique_ptr<ElementRenderer> render() override;

        void setPaddings(int paddings);

        void setPaddings(int paddingY, int paddingX);

        void setPaddings(int paddingTop, int paddingX, int paddingBottom);

        void setPaddings(int paddingTop, int paddingRight, int paddingBottom, int paddingLeft);
    };

    class PaddingRenderer : public ElementRenderer {
    public:
        PaddingsValue paddings;
        Element *child;

        std::vector<RenderElement> getChildren(RenderSize size) override;
    };
}


#endif //ELEMENTOR_PADDING_H

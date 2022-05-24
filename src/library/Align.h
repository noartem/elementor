//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_ALIGN_H
#define ELEMENTOR_ALIGN_H

#include "Element.h"

namespace elementor {
    struct AlignmentFraction {
        float x;
        float y;
    };

    enum class Alignment {
        BottomCenter,
        BottomLeft,
        BottomRight,
        Center,
        CenterLeft,
        CenterRight,
        TopCenter,
        TopLeft,
        TopRight,
    };

    class Align : public Element, WithChild {
    public:
        Align *setAlignment(Alignment alignment);

        Align *setAlignment(AlignmentFraction alignment);

        AlignmentFraction getAlignment();

        Align *setChild(Element *child);

        std::vector <RenderElement> getRenderChildren(ApplicationContext *ctx, Size size) override;

    private:
        AlignmentFraction alignment = {0.5, 0.5};
    };

    Align *align();
}


#endif //ELEMENTOR_ALIGN_H

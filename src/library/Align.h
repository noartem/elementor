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

    class Align : public Element, public WithChild {
    public:
        Align *setAlignment(Alignment alignment);

        Align *setAlignment(AlignmentFraction alignment);

        AlignmentFraction getAlignment();

        Align *setChild(Element *child);

        std::shared_ptr <ElementRenderer> render() override;
    
    private:
        AlignmentFraction alignment = {0.5, 0.5};
    };

    Align *align();

    class AlignRenderer : public ElementRenderer {
    public:
        AlignRenderer(ApplicationContext *context, AlignmentFraction alignment, Element *child);

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        AlignmentFraction alignment;
        Element *child;    
    };
}


#endif //ELEMENTOR_ALIGN_H

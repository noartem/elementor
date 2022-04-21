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

    class Align : public Element {
    public:
        Element *child;

        void setAlignment(Alignment alignment);

        void setAlignment(AlignmentFraction alignment);

        std::shared_ptr <ElementRenderer> render() override;
    
    private:
        AlignmentFraction alignment;
    };

    class AlignRenderer : public ElementRenderer {
    public:
        AlignmentFraction alignment;
        Element *child;

        std::vector <RenderElement> getChildren(RenderSize size) override;
    };
}


#endif //ELEMENTOR_ALIGN_H

//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_FLEX_H
#define ELEMENTOR_FLEX_H

#include "Element.h"

namespace elementor {
    enum class FlexDirection {
        Row,
        Column,
    };

    enum class FlexAlignment {
        Start,
        Center,
        End,
    };

    enum class FlexCrossAlignment {
        Start,
        SpaceBetween,
        SpaceEvenly,
        End,
    };

    class Flex : public Element {
    public:
        int spacing = 0;
        FlexDirection direction = FlexDirection::Row;
        FlexAlignment alignment = FlexAlignment::Start;
        FlexCrossAlignment crossAlignment = FlexCrossAlignment::Start;
        std::vector<Element *> children;

        std::shared_ptr <ElementRenderer> render() override;
    };

    class FlexRenderer : public ElementRenderer {
    public:
        int spacing;
        FlexDirection direction;
        FlexAlignment alignment;
        FlexCrossAlignment crossAlignment;
        std::vector<Element *> children;

        std::vector <RenderElement> getChildren(RenderSize size) override;
    };
}


#endif //ELEMENTOR_FLEX_H

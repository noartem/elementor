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

    class Flex : public Element, public WithChildren {
    public:
        Flex *setSpacing(float spacing);

        float getSpacing();

        Flex *setDirection(FlexDirection direction);

        FlexDirection getDirection();

        Flex *setAlignment(FlexAlignment alignment);

        FlexAlignment getAlignment();

        Flex *setCrossAlignment(FlexCrossAlignment alignment);

        FlexCrossAlignment getCrossAlignment();

        Flex *appendChild(Element *child);

        std::shared_ptr <ElementRenderer> render() override;

    private:
        float spacing = 0;
        FlexDirection direction = FlexDirection::Row;
        FlexAlignment alignment = FlexAlignment::Start;
        FlexCrossAlignment crossAlignment = FlexCrossAlignment::Start;
    };

    Flex *flex();

    class FlexRenderer : public ElementRenderer {
    public:
        FlexRenderer(ApplicationContext *context, float spacing, FlexDirection direction, FlexAlignment alignment, FlexCrossAlignment crossAlignment, std::vector<Element *> children);

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        int spacing;
        FlexDirection direction;
        FlexAlignment alignment;
        FlexCrossAlignment crossAlignment;
        std::vector<Element *> children;
    };
}


#endif //ELEMENTOR_FLEX_H

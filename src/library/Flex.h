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
        Center,
        End,
        SpaceBetween,
        SpaceEvenly,
    };

    class Flex : public Element, WithChildren {
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

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

    private:
        float spacing = 0;
        FlexDirection direction = FlexDirection::Row;
        FlexAlignment alignment = FlexAlignment::Start;
        FlexCrossAlignment crossAlignment = FlexCrossAlignment::Start;
    };

    Flex *flex();
}


#endif //ELEMENTOR_FLEX_H

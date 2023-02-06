//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_FLEX_H
#define ELEMENTOR_FLEX_H

#include "../Element.h"

namespace elementor::elements {
    enum class FlexDirection {
        Row,
        Column,
    };

    enum class FlexAlignment {
        Start,
        Center,
        End,
        Stretch,
    };

    enum class FlexCrossAlignment {
        Start,
        Center,
        End,
        SpaceBetween,
        SpaceEvenly,
    };

    class Flex : public Element, public WithChildren, public std::enable_shared_from_this<Flex> {
    public:
        std::shared_ptr<Flex> setSpacing(float newSpacing);

        float getSpacing() const;

        std::shared_ptr<Flex> setDirection(FlexDirection newDirection);

        FlexDirection getDirection();

        std::shared_ptr<Flex> setAlignment(FlexAlignment newAlignment);

        FlexAlignment getAlignment();

        std::shared_ptr<Flex> setCrossAlignment(FlexCrossAlignment newAlignment);

        FlexCrossAlignment getCrossAlignment();

        std::shared_ptr<Flex> appendChild(const std::shared_ptr<Element>& child);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        std::vector<RenderElement>
        getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    private:
        float spacing = 0;
        FlexDirection direction = FlexDirection::Row;
        FlexAlignment alignment = FlexAlignment::Start;
        FlexCrossAlignment crossAlignment = FlexCrossAlignment::Start;
    };

    std::shared_ptr<Flex> flex();
}


#endif //ELEMENTOR_FLEX_H

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
        Flex() {};

        Flex(std::vector<Element *> children);

        Flex(FlexDirection direction, std::vector<Element *> children);

        Flex(FlexAlignment alignment, std::vector<Element *> children);

        Flex(FlexCrossAlignment crossAlignment, std::vector<Element *> children);

        Flex(FlexAlignment alignment, FlexCrossAlignment crossAlignment, std::vector<Element *> children);

        Flex(FlexDirection direction, FlexAlignment alignment, std::vector<Element *> children);

        Flex(FlexDirection direction, FlexCrossAlignment crossAlignment, std::vector<Element *> children);

        Flex(FlexDirection direction, FlexAlignment alignment, FlexCrossAlignment crossAlignment, std::vector<Element *> children);

        Flex(float spacing, std::vector<Element *> children);

        Flex(float spacing, FlexDirection direction, std::vector<Element *> children);

        Flex(float spacing, FlexAlignment alignment, std::vector<Element *> children);

        Flex(float spacing, FlexDirection direction, FlexAlignment alignment, std::vector<Element *> children);

        Flex(float spacing, FlexCrossAlignment crossAlignment, std::vector<Element *> children);

        Flex(float spacing, FlexDirection direction, FlexCrossAlignment crossAlignment, std::vector<Element *> children);

        Flex(float spacing, FlexAlignment alignment, FlexCrossAlignment crossAlignment, std::vector<Element *> children);

        Flex(float spacing, FlexDirection direction, FlexAlignment alignment, FlexCrossAlignment crossAlignment, std::vector<Element *> children);

        void setSpacing(float spacing);

        float getSpacing();

        void setDirection(FlexDirection direction);

        FlexDirection getDirection();

        void setAlignment(FlexAlignment alignment);

        FlexAlignment getAlignment();

        void setCrossAlignment(FlexCrossAlignment alignment);

        FlexCrossAlignment getCrossAlignment();

        std::shared_ptr <ElementRenderer> render() override;

    private:
        float spacing = 0;
        FlexDirection direction = FlexDirection::Row;
        FlexAlignment alignment = FlexAlignment::Start;
        FlexCrossAlignment crossAlignment = FlexCrossAlignment::Start;
    };

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

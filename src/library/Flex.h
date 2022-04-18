//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_FLEX_H
#define ELEMENTOR_FLEX_H

#include "Element.h"

namespace elementor {
    enum FlexDirection { Row, Column };

    class Flex : public Element {
    public:
        int gap = 0;
        FlexDirection direction = FlexDirection::Row;
        std::vector<Element*> children;

        std::unique_ptr<ElementRenderer> render() override;
    };

    class FlexRenderer : public ElementRenderer {
    public:
        int gap = 0;
        FlexDirection direction = FlexDirection::Row;
        std::vector<Element*> children;

        std::vector<RenderElement> getChildren(RenderSize size) override;
    };
}


#endif //ELEMENTOR_FLEX_H

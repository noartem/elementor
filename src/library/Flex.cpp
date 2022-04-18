//
// Created by noartem on 13.04.2022.
//

#include "Flex.h"

namespace elementor {
    std::unique_ptr <ElementRenderer> Flex::render() {
        auto renderer = std::make_unique<FlexRenderer>();
        renderer->gap = this->gap;
        renderer->direction = this->direction;
        renderer->children = this->children;
        return renderer;
    }

    std::vector <RenderElement> FlexRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        int axisSize = this->direction == FlexDirection::Row ? size.width : size.height;
        int childrenCount = this->children.size();
        int itemSize = (axisSize - (childrenCount - 1) * this->gap) / childrenCount;

        for (int i = 0; i < childrenCount; i++) {
            RenderElement child;
            child.element = this->children[i];

            int axisPosition = (itemSize + this->gap) * i;
            if (this->direction == FlexDirection::Row) {
                child.position = {axisPosition, 0};
            } else {
                child.position = {0, axisPosition};
            }

            if (this->direction == FlexDirection::Row) {
                child.size = {itemSize, size.height};
            } else {
                child.size = {size.width, itemSize};
            }

            children.push_back(child);
        }

        return children;
    }
}

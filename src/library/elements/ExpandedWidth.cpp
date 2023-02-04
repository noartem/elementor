//
// Created by noartem on 18.06.2022.
//

#include "ExpandedWidth.h"

namespace elementor::elements {
    ExpandedWidth *expandedWidth() {
        return new ExpandedWidth();
    }

    ExpandedWidth *ExpandedWidth::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size ExpandedWidth::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        return fitSizeInBoundaries(this->getChild()->getSize(ctx, window, {{boundaries.max.width, 0}, boundaries.max}), boundaries);
    }

    std::vector <RenderElement> ExpandedWidth::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        RenderElement childElement{this->getChild(), {0, 0}, rect.size};
        return {childElement};
    }
}

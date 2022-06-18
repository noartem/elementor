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

    Size ExpandedWidth::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        return fitSizeInBoundaries(this->getChild()->getSize(ctx, {{boundaries.max.width, 0}, boundaries.max}), boundaries);
    }

    std::vector <RenderElement> ExpandedWidth::getChildren(ApplicationContext *ctx, Size size) {
        RenderElement child;
        child.element = this->getChild();
        child.position = {0, 0};
        child.size = size;
        return {child};
    }
}

//
// Created by noartem on 18.06.2022.
//

#include "ExpandedHeight.h"

namespace elementor::elements {
    ExpandedHeight *expandedHeight() {
        return new ExpandedHeight();
    }

    ExpandedHeight *ExpandedHeight::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size ExpandedHeight::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        return fitSizeInBoundaries(this->getChild()->getSize(ctx, window, {{0, boundaries.max.height}, boundaries.max}), boundaries);
    }

    std::vector <RenderElement> ExpandedHeight::getChildren(ApplicationContext *ctx, Window *window, Size size) {
        RenderElement child;
        child.element = this->getChild();
        child.position = {0, 0};
        child.size = size;
        return {child};
    }
}

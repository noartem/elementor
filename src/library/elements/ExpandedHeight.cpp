//
// Created by noartem on 18.06.2022.
//

#include "ExpandedHeight.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<ExpandedHeight> expandedHeight() {
        return std::make_shared<ExpandedHeight>();
    }

    std::shared_ptr<ExpandedHeight> ExpandedHeight::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size ExpandedHeight::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        return fitSizeInBoundaries(this->getChild()->getSize(ctx, window, {{0, boundaries.max.height}, boundaries.max}), boundaries);
    }

    std::vector <RenderElement> ExpandedHeight::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        RenderElement childElement{this->getChild(), {0, 0}, rect.size};
        return {childElement};
    }
}

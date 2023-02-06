//
// Created by noartem on 18.06.2022.
//

#include "ExpandedWidth.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<ExpandedWidth>  expandedWidth() {
        return std::make_shared<ExpandedWidth>();
    }

    std::shared_ptr<ExpandedWidth>  ExpandedWidth::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size ExpandedWidth::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        return fitSizeInBoundaries(this->getChild()->getSize(ctx, window, {{boundaries.max.width, 0}, boundaries.max}), boundaries);
    }

    std::vector <RenderElement> ExpandedWidth::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        RenderElement childElement{this->getChild(), {0, 0}, rect.size};
        return {childElement};
    }
}

//
// Created by noartem on 27.07.2022.
//

#include "FitContain.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<FitContain> fitContain() {
        return std::make_shared<FitContain>();
    }

    std::shared_ptr<FitContain> FitContain::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size fitSizeWithin(Size inner, Size outer) {
        float innerRatio = inner.width / inner.height;
        float outerRatio = outer.width / outer.height;
        float resizeFactor = (innerRatio >= outerRatio) ? (outer.width / inner.width) : (outer.height / inner.height);
        return {inner.width * resizeFactor, inner.height * resizeFactor};
    }

    std::vector<RenderElement>
    FitContain::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        RenderElement childElement{};
        childElement.element = this->getChild();
        Size childSize = childElement.element->getSize(ctx, window, {{0, 0},
                                                                     {INFINITY, INFINITY}});
        childElement.size = fitSizeWithin(childSize, rect.size);
        childElement.position.x = (rect.size.width - childElement.size.width) / 2;
        childElement.position.y = (rect.size.height - childElement.size.height) / 2;
        return {childElement};
    }
}

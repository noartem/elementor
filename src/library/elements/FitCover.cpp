//
// Created by noartem on 27.07.2022.
//

#include "FitCover.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<FitCover> fitCover() {
        return std::make_shared<FitCover>();
    }

    std::shared_ptr<FitCover> FitCover::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    ClipBehavior FitCover::getClipBehaviour() {
        return ClipBehavior::AntiAlias;
    }

    std::vector <RenderElement> FitCover::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        RenderElement childElement;
        childElement.element = this->getChild();

        Size childSize = childElement.element->getSize(ctx, window, {{0, 0}, {INFINITY, INFINITY}});
        float ratio = childSize.width / childSize.height;
        if (rect.size.width > rect.size.height) {
            childElement.size.width = rect.size.width;
            childElement.size.height = rect.size.width / ratio;
        } else {
            childElement.size.height = rect.size.height;
            childElement.size.width = rect.size.height / ratio;
        }

        childElement.position.x = (rect.size.width - childElement.size.width) / 2;
        childElement.position.y = (rect.size.height - childElement.size.height) / 2;

        return {childElement};
    }
}

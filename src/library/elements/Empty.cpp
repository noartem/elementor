//
// Created by noartem on 29.05.2022.
//

#include "Empty.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<Empty> empty() {
        return std::make_shared<Empty>();
    }

    std::shared_ptr<Empty> Empty::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size Empty::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.min;
        }
    }

    std::vector <RenderElement> Empty::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }
}

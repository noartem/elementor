//
// Created by noartem on 13.04.2022.
//

#include "Flexible.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<Flexible> flexible() {
        return std::make_shared<Flexible>();
    }

    std::shared_ptr<Flexible> Flexible::setGrow(float newGrow) {
        this->grow = newGrow;
        return shared_from_this();
    }

    float Flexible::getGrow() const {
        return this->grow;
    }

    std::shared_ptr<Flexible> Flexible::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size Flexible::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        return fitSizeInBoundaries(this->getChild()->getSize(ctx, window, boundaries), boundaries);
    }

    std::vector <RenderElement> Flexible::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }
}

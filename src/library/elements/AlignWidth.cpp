//
// Created by noartem on 29.05.2022.
//

#include "AlignWidth.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<AlignWidth> alignWidth() {
        return std::make_shared<AlignWidth>();
    }

    std::shared_ptr<AlignWidth> AlignWidth::setCoef(float newCoef, float newChildCoef) {
        this->coef = newCoef;
        this->childCoef = newChildCoef;
        return shared_from_this();
    }

    std::shared_ptr<AlignWidth> AlignWidth::setCoef(float newCoef) {
        this->setCoef(newCoef, newCoef);
        return shared_from_this();
    }

    float AlignWidth::getCoef() const {
        return this->coef;
    }

    float AlignWidth::getChildCoef() const {
        return this->childCoef;
    }

    std::shared_ptr<AlignWidth> AlignWidth::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size AlignWidth::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                             Boundaries boundaries) {
        if (this->hasChild()) {
            Boundaries childBoundaries = {{0, boundaries.min.height}, boundaries.max};
            Size childSize = this->getChild()->getSize(ctx, window, childBoundaries);
            return fitSizeInBoundaries(childSize, {{boundaries.max.width, boundaries.min.height}, boundaries.max});
        } else {
            return boundaries.max;
        }
    }

    std::vector<RenderElement>
    AlignWidth::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector<RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.size = child.element->getSize(ctx, window, {{0, rect.size.height}, rect.size});
            child.position = {rect.size.width * this->coef - child.size.width * this->childCoef, 0};

            children.push_back(child);
        }

        return children;
    }
}

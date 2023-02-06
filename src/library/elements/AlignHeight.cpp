//
// Created by noartem on 29.05.2022.
//

#include "AlignHeight.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<AlignHeight> alignHeight() {
        return std::make_shared<AlignHeight>();
    }

    std::shared_ptr<AlignHeight> AlignHeight::setCoef(float newCoef, float newChildCoef) {
        this->coef = newCoef;
        this->childCoef = newChildCoef;
        return shared_from_this();
    }

    std::shared_ptr<AlignHeight> AlignHeight::setCoef(float newCoef) {
        this->setCoef(newCoef, newCoef);
        return shared_from_this();
    }

    float AlignHeight::getCoef() const {
        return this->coef;
    }

    float AlignHeight::getChildCoef() const {
        return this->childCoef;
    }

    std::shared_ptr<AlignHeight> AlignHeight::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size AlignHeight::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                              Boundaries boundaries) {
        if (this->hasChild()) {
            Boundaries childBoundaries = {{boundaries.min.width, 0}, boundaries.max};
            Size childSize = this->getChild()->getSize(ctx, window, childBoundaries);
            return fitSizeInBoundaries(childSize, {{boundaries.min.width, boundaries.max.height}, boundaries.max});
        } else {
            return boundaries.max;
        }
    }

    std::vector<RenderElement>
    AlignHeight::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                             ElementRect rect) {
        std::vector<RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.size = child.element->getSize(ctx, window, {{rect.size.width,}, rect.size});
            child.position = {0, rect.size.height * this->coef - child.size.height * this->childCoef};

            children.push_back(child);
        }

        return children;
    }
}

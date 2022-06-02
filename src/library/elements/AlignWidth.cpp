//
// Created by noartem on 29.05.2022.
//

#include "AlignWidth.h"

namespace elementor::elements {
    AlignWidth *alignWidth() {
        return new AlignWidth();
    }

    AlignWidth *AlignWidth::setCoef(float coef, float childCoef) {
        this->coef = coef;
        this->childCoef = childCoef;
        return this;
    }

    AlignWidth *AlignWidth::setCoef(float coef) {
        this->setCoef(coef, coef);
        return this;
    }

    float AlignWidth::getCoef() {
        return this->coef;
    }

    float AlignWidth::getChildCoef() {
        return this->childCoef;
    }

    AlignWidth *AlignWidth::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size AlignWidth::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->hasChild()) {
            Boundaries childBoundaries = {{0, boundaries.min.height}, boundaries.max};
            Size childSize = this->getChild()->getSize(ctx, childBoundaries);
            return fitSizeInBoundaries(childSize, {{boundaries.max.width, boundaries.min.height}, boundaries.max});
        } else {
            return boundaries.max;
        }
    }

    std::vector <RenderElement> AlignWidth::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.size = child.element->getSize(ctx, {{0, size.height}, size});
            child.position = {(int) ceil(size.width * this->coef - child.size.width * this->childCoef), 0};

            children.push_back(child);
        }

        return children;
    }
}

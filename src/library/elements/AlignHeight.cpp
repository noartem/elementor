//
// Created by noartem on 29.05.2022.
//

#include "AlignHeight.h"

namespace elementor::elements {
    AlignHeight *alignHeight() {
        return new AlignHeight();
    }

    AlignHeight *AlignHeight::setCoef(float coef, float childCoef) {
        this->coef = coef;
        this->childCoef = childCoef;
        return this;
    }

    AlignHeight *AlignHeight::setCoef(float coef) {
        this->setCoef(coef, coef);
        return this;
    }

    float AlignHeight::getCoef() {
        return this->coef;
    }

    float AlignHeight::getChildCoef() {
        return this->childCoef;
    }

    AlignHeight *AlignHeight::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size AlignHeight::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->hasChild()) {
            Boundaries childBoundaries = {{boundaries.min.width, 0}, boundaries.max};
            Size childSize = this->getChild()->getSize(ctx, childBoundaries);
            return fitSizeInBoundaries(childSize, {{boundaries.min.width, boundaries.max.height}, boundaries.max});
        } else {
            return boundaries.max;
        }
    }

    std::vector <RenderElement> AlignHeight::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.size = child.element->getSize(ctx, {{size.width, }, size});
            child.position = {0, size.height * this->coef - child.size.height * this->childCoef};

            children.push_back(child);
        }

        return children;
    }
}

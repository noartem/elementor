//
// Created by noartem on 13.04.2022.
//

#include "Flexible.h"

namespace elementor::elements {
    Flexible *flexible() {
        return new Flexible();
    }

    Flexible *Flexible::setGrow(float grow) {
        this->grow = grow;
        return this;
    }

    float Flexible::getGrow() {
        return this->grow;
    }

    Flexible *Flexible::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Flexible::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        return fitSizeInBoundaries(this->getChild()->getSize(ctx, window, boundaries), boundaries);
    }

    std::vector <RenderElement> Flexible::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }
}

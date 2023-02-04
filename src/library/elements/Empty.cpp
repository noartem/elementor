//
// Created by noartem on 29.05.2022.
//

#include "Empty.h"

namespace elementor::elements {
    Empty *empty() {
        return new Empty();
    }

    Empty *Empty::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Empty::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.min;
        }
    }

    std::vector <RenderElement> Empty::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }
}

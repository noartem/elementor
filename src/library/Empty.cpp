//
// Created by noartem on 29.05.2022.
//

#include "Empty.h"

namespace elementor {
    Empty *empty() {
        return new Empty();
    }

    Empty *Empty::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Empty::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        return boundaries.min;
    }

    std::vector <RenderElement> Empty::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.size = size;
            child.position = {0, 0};

            children.push_back(child);
        }

        return children;
    }
}

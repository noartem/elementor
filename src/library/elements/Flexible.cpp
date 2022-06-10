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

    std::vector <RenderElement> Flexible::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.position = {0, 0};
            child.size = size;

            children.push_back(child);
        }

        return children;
    }
}

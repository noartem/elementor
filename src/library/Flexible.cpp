//
// Created by noartem on 13.04.2022.
//

#include "Flexible.h"

namespace elementor {
    Flexible *flexible() {
        return new Flexible();
    }

    Flexible *Flexible::setGrow(int grow) {
        this->grow = grow;
        return this;
    }

    int Flexible::getGrow() {
        return this->grow;
    }

    Flexible *Flexible::setChild(Element *child) {
        child->context = context;
        this->updateChild(child);
        return this;
    }

    std::vector <RenderElement> Flexible::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild(this->context);
            child.position = {0, 0};
            child.size = child.element->getSize({{0, 0}, size});

            children.push_back(child);
        }

        return children;
    }
}

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
        this->updateChild(child);
        return this;
    }

    std::shared_ptr <ElementRenderer> Flexible::render() {
        return std::make_shared<FlexibleRenderer>(this->context, this->getChild());
    }

    FlexibleRenderer::FlexibleRenderer(ApplicationContext *context, Element *child) {
        this->context = context;
        this->child = child;
    }

    std::vector <RenderElement> FlexibleRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement child;
            child.element = this->child;
            child.element->context = context;
            child.renderer = this->child->render();
            child.position = {0, 0};
            child.size = child.renderer->getSize({{0, 0}, size});

            children.push_back(child);
        }

        return children;
    }
}

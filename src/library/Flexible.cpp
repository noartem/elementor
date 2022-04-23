//
// Created by noartem on 13.04.2022.
//

#include "Flexible.h"

namespace elementor {
    Flexible::Flexible(Element *child) {
        this->setChild(child);
    }

    Flexible::Flexible(int grow, Element *child) {
        this->setGrow(grow);
        this->setChild(child);
    }

    void Flexible::setGrow(int grow) {
        this->grow = grow;
    }

    int Flexible::getGrow() {
        return this->grow;
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

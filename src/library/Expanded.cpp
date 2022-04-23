//
// Created by noartem on 13.04.2022.
//

#include "Expanded.h"

namespace elementor {
    Expanded::Expanded(Element *child) {
        this->setChild(child);
    }

    Expanded::Expanded(int grow, Element *child) {
        this->setGrow(grow);
        this->setChild(child);
    }

    void Expanded::setGrow(int grow) {
        this->grow = grow;
    }

    int Expanded::getGrow() {
        return this->grow;
    }

    std::shared_ptr <ElementRenderer> Expanded::render() {
        return std::make_shared<ExpandedRenderer>(this->context, this->getChild());
    }

    ExpandedRenderer::ExpandedRenderer(ApplicationContext *context, Element *child) {
        this->context = context;
        this->child = child;
    }

    std::vector <RenderElement> ExpandedRenderer::getChildren(RenderSize size) {
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

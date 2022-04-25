//
// Created by noartem on 20.04.2022.
//

#include "Expanded.h"

namespace elementor {
    Expanded *expanded() {
        return new Expanded();
    }

    Expanded *Expanded::setGrow(int grow) {
        this->grow = grow;
        return this;
    }

    int Expanded::getGrow() {
        return this->grow;
    }

    Expanded *Expanded::setChild(Element *child) {
        this->updateChild(child);
        return this;
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

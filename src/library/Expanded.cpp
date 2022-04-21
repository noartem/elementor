//
// Created by noartem on 13.04.2022.
//

#include "Expanded.h"

namespace elementor {
    std::shared_ptr <ElementRenderer> Expanded::render() {
        auto renderer = std::make_shared<ExpandedRenderer>();
        renderer->child = this->child;
        renderer->context = this->context;
        return renderer;
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

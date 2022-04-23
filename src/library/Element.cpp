//
// Created by noartem on 16.04.2022.
//

#include "Element.h"

namespace elementor {
    std::shared_ptr <ElementRenderer> Element::render() {
        auto renderer = std::make_shared<ElementRenderer>();
        renderer->context = this->context;
        return renderer;
    }

    RenderSize ElementRenderer::getSize(RenderBoundaries boundaries) {
        return boundaries.max;
    }

    void ElementRenderer::paintBackground(SkCanvas *canvas, RenderSize size) {
    }

    std::vector <RenderElement> ElementRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;
        return children;
    }

    void ElementWithChild::setChild(Element *element) {
        this->child = element;
    }

    void ElementWithChild::removeChild() {
        this->setChild(NULL);
    }

    Element *ElementWithChild::getChild() {
        return this->child;
    }
}

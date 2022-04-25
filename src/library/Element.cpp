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

    void WithChild::updateChild(Element *element) {
        this->child = element;
    }

    void WithChild::removeChild() {
        this->updateChild(NULL);
    }

    Element *WithChild::getChild() {
        return this->child;
    }

    void WithChildren::setChildren(std::vector<Element *> children) {
        this->children = children;
    }

    void WithChildren::addChild(Element *child) {
        this->children.push_back(child);
    }

    void WithChildren::removeChild(int i) {
        this->children.erase(this->children.begin() + i); 
    }

    std::vector<Element *> WithChildren::getChildren() {
        return this->children;
    }

    Element *WithChildren::getChild(int i) {
        return this->children[i];
    }
}

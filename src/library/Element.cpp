//
// Created by noartem on 16.04.2022.
//

#include "Element.h"

namespace elementor {
    RenderSize Element::getSize(RenderBoundaries boundaries) {
        return boundaries.max;
    }

    void Element::paintBackground(SkCanvas *canvas, RenderSize size) {
    }

    std::vector <RenderElement> Element::getChildren(RenderSize size) {
        std::vector <RenderElement> children;
        return children;
    }

    void WithChild::updateChild(Element *element) {
        this->child = element;
    }

    void WithChild::removeChild() {
        this->updateChild(NULL);
    }

    Element *WithChild::getChild(ApplicationContext *context) {
        if (this->child) {
            this->child->context = context;
            return this->child;
        } else {
            return NULL;
        }
    }

    bool WithChild::hasChild() {
        return this->child != NULL;
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

    int WithChildren::getChildrenSize() {
        return this->children.size();
    }

    Element *WithChildren::getChild(int i) {
        return this->children[i];
    }
}

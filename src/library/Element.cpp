//
// Created by noartem on 16.04.2022.
//

#include "Element.h"

#include <algorithm>

namespace elementor {
    Size Element::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        return boundaries.max;
    }

    void Element::paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) {
    }

    std::vector <RenderElement> Element::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector <RenderElement> children;
        return children;
    }

    ClipBehavior Element::getClipBehaviour() {
        return ClipBehavior::None;
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

    std::vector<Element *> WithChildren::getChildrenList() {
        return this->children;
    }

    int WithChildren::getChildrenSize() {
        return this->children.size();
    }

    Element *WithChildren::getChild(int i) {
        return this->children[i];
    }

    int WithChildren::childIndex(Element *child) {
        for (int i = 0; i < this->children.size(); i++) {
            if (this->children[i] == child) {
                return i;
            }
        }
        return -1;
    }
}

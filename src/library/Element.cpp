//
// Created by noartem on 16.04.2022.
//

#include "Element.h"

#include <algorithm>

namespace elementor {
    Size Element::getSize(Boundaries boundaries) {
        return boundaries.max;
    }

    void Element::paintBackground(SkCanvas *canvas, ElementRect rect) {
    }

    std::vector <RenderElement> Element::getRenderChildren(Size size) {
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

    Size fitSizeInBoundaries(Size size, Boundaries boundaries) {
        int width = std::min(std::max(size.width, boundaries.min.width), boundaries.max.width);
        int height = std::min(std::max(size.height, boundaries.min.height), boundaries.max.height);
        return {width, height};
    }

    Rect clipRectInParent(Rect childRect, Rect parentRect) {
        Rect rect;
        rect.position.x = childRect.position.x;
        rect.position.y = childRect.position.y;
        rect.size.width = std::min(parentRect.size.width - childRect.position.x, childRect.size.width);
        rect.size.height = std::min(parentRect.size.height - childRect.position.y, childRect.size.height);
        return rect;
    }
}

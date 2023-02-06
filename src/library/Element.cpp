//
// Created by noartem on 16.04.2022.
//

#include "Element.h"

#include <algorithm>
#include <utility>

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

    WithChild::~WithChild() {
        delete this->child;
    }

    void WithChild::updateChild(Element *element) {
        delete this->child;
        this->child = element;
    }

    void WithChild::removeChild() {
        this->updateChild(nullptr);
    }

    Element *WithChild::getChild() const {
        return this->child;
    }

    bool WithChild::hasChild() const {
        return this->child != nullptr;
    }

    WithChildren::~WithChildren() {
        for (auto child : children) {
            delete child;
        }
    }

    void WithChildren::setChildren(std::vector<Element *> newChildren) {
        for (Element *child : this->children) {
            delete child;
        }

        this->children = std::move(newChildren);
    }

    void WithChildren::clearChildren() {
        this->setChildren({});
    }

    void WithChildren::addChild(Element *child) {
        this->children.push_back(child);
    }

    void WithChildren::removeChild(int i) {
        if (i >= 0 && i < this->children.size()) {
            delete this->children[i];
            this->children.erase(this->children.begin() + i);
        }
    }

    void WithChildren::removeChild(Element *child) {
        this->removeChild(this->childIndex(child));
    }

    std::vector<Element *> WithChildren::getChildrenList() const {
        return this->children;
    }

    size_t WithChildren::getChildrenSize() const {
        return this->children.size();
    }

    Element *WithChildren::getChild(int i) const {
        return this->children[i];
    }

    int WithChildren::childIndex(Element *child) const {
        for (int i = 0; i < this->children.size(); i++) {
            if (this->children[i] == child) {
                return i;
            }
        }
        return -1;
    }
}

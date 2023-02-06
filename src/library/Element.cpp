//
// Created by noartem on 16.04.2022.
//

#include "Element.h"

#include <algorithm>
#include <utility>

namespace elementor {
    Size Element::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        return boundaries.max;
    }

    void Element::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) {
    }

    std::vector <RenderElement> Element::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector <RenderElement> children;
        return children;
    }

    ClipBehavior Element::getClipBehaviour() {
        return ClipBehavior::None;
    }

    void WithChild::updateChild(const std::shared_ptr<Element>& element) {
        this->child = element;
    }

    void WithChild::removeChild() {
        this->updateChild(nullptr);
    }

    std::shared_ptr<Element> WithChild::getChild() const {
        return this->child;
    }

    bool WithChild::hasChild() const {
        return this->child != nullptr;
    }

    void WithChildren::setChildren(std::vector<std::shared_ptr<Element>> newChildren) {
        this->children = std::move(newChildren);
    }

    void WithChildren::clearChildren() {
        this->setChildren({});
    }

    void WithChildren::addChild(const std::shared_ptr<Element>& child) {
        this->children.push_back(child);
    }

    void WithChildren::removeChild(int i) {
        if (i >= 0 && i < this->children.size()) {
            this->children.erase(this->children.begin() + i);
        }
    }

    void WithChildren::removeChild(const std::shared_ptr<Element>& child) {
        this->removeChild(this->childIndex(std::move(child)));
    }

    std::vector<std::shared_ptr<Element>> WithChildren::getChildrenList() const {
        return this->children;
    }

    size_t WithChildren::getChildrenSize() const {
        return this->children.size();
    }

    std::shared_ptr<Element> WithChildren::getChild(int i) const {
        return this->children[i];
    }

    int WithChildren::childIndex(const std::shared_ptr<Element>& child) const {
        for (int i = 0; i < this->children.size(); i++) {
            if (this->children[i] == child) {
                return i;
            }
        }
        return -1;
    }
}

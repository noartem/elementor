//
// Created by noartem on 04.02.2023.
//

#include "Tooltip.h"
#include "ComponentsContext.h"

namespace elementor::components {
    Tooltip *tooltip() {
        return new Tooltip();
    }

    Tooltip::~Tooltip() {
        if (this->window) {
            auto stackElement = this->getStackElement();
            stackElement->removeChild(this->tipPadding);
        } else {
            delete this->tipPadding;
        }

        delete this->child;
    }

    Tooltip *Tooltip::setActive(bool newActive) {
        this->active = newActive;
        return this;
    }

    Tooltip *Tooltip::toggleActive() {
        return this->setActive(!this->active);
    }

    bool Tooltip::getActive() const {
        return this->active;
    }

    Tooltip *Tooltip::setChild(Element *newChild) {
        this->child = newChild;
        return this;
    }

    Element *Tooltip::getChild() const {
        return this->child;
    }

    Tooltip *Tooltip::setTip(Element *newTip) {
        this->tip = newTip;
        this->tipPadding->setChild(this->tip);
        return this;
    }

    Element *Tooltip::getTip() {
        return this->tip;
    }

    Size Tooltip::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        return this->child->getSize(ctx, window, boundaries);
    }

    std::vector<RenderElement> Tooltip::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector<RenderElement> children;

        children.push_back({this->child, {0, 0}, rect.size});

        auto componentsContext = static_cast<ComponentsContext *>(window->getUserPointer());
        auto stackElement = componentsContext->getStackElement();
        auto stackChildren = stackElement->getChildrenList();
        int tipPaddingIndex = stackElement->childIndex(this->tipPadding);

        if (this->active) {
            if (tipPaddingIndex == -1) {
                stackElement->appendChild(this->tipPadding);
            }

            auto tipSize = this->tip->getSize(ctx, window, {{0, 0},
                                                            {INFINITY, INFINITY}});
            auto tipX = rect.position.x + rect.size.width / 2 - tipSize.width / 2;
            auto tipY = rect.position.y + rect.visibleSize.height + 4;
            this->tipPadding->setPaddings(tipY, window->getSize().width - tipX - tipSize.width,
                                          window->getSize().height - tipY - tipSize.height, tipX);
        } else {
            if (tipPaddingIndex != -1) {
                stackElement->removeChild(tipPaddingIndex);
            }
        }

        return children;
    }
}
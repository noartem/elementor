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

    Tooltip *Tooltip::setPlacement(TooltipPlacement newPlacement) {
        this->placement = newPlacement;
        return this;
    }

    TooltipPlacement Tooltip::getPlacement() const {
        return this->placement;
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

    Stack *Tooltip::getStackElement() {
        auto componentsContext = static_cast<ComponentsContext *>(window->getUserPointer());
        return componentsContext->getStackElement();
    }

    std::vector<RenderElement>
    Tooltip::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        this->window = window;

        std::vector<RenderElement> children;
        children.push_back({this->child, {0, 0}, rect.size});

        auto stackElement = this->getStackElement();
        int tipPaddingIndex = stackElement->childIndex(this->tipPadding);
        if (this->active) {
            if (tipPaddingIndex == -1) {
                stackElement->appendChild(this->tipPadding);
            }

            auto tipSize = this->tip->getSize(ctx, window, {{0, 0},
                                                            {INFINITY, INFINITY}});

            float tipX = 0;
            if (this->placement == TooltipPlacement::TopStart || this->placement == TooltipPlacement::BottomStart) {
                tipX = rect.position.x;
            } else if (this->placement == TooltipPlacement::Top || this->placement == TooltipPlacement::Bottom) {
                tipX = rect.position.x + rect.size.width / 2 - tipSize.width / 2;
            } else if (this->placement == TooltipPlacement::TopEnd || this->placement == TooltipPlacement::BottomEnd) {
                tipX = rect.position.x + rect.size.width - tipSize.width;
            } else if (this->placement == TooltipPlacement::LeftStart || this->placement == TooltipPlacement::Left ||
                       this->placement == TooltipPlacement::LeftEnd) {
                tipX = rect.position.x - tipSize.width;
            } else if (this->placement == TooltipPlacement::RightStart || this->placement == TooltipPlacement::Right ||
                       this->placement == TooltipPlacement::RightEnd) {
                tipX = rect.position.x + rect.size.width;
            }

            float tipY = 0;
            if (this->placement == TooltipPlacement::LeftStart || this->placement == TooltipPlacement::RightStart) {
                tipY = rect.position.y;
            } else if (this->placement == TooltipPlacement::Left || this->placement == TooltipPlacement::Right) {
                tipY = rect.position.y + rect.size.height / 2 - tipSize.height / 2;
            } else if (this->placement == TooltipPlacement::LeftEnd || this->placement == TooltipPlacement::RightEnd) {
                tipY = rect.position.y + rect.size.height - tipSize.height;
            } else if (this->placement == TooltipPlacement::TopStart || this->placement == TooltipPlacement::Top ||
                       this->placement == TooltipPlacement::TopEnd) {
                tipY = rect.position.y - tipSize.height;
            } else if (this->placement == TooltipPlacement::BottomStart ||
                       this->placement == TooltipPlacement::Bottom || this->placement == TooltipPlacement::BottomEnd) {
                tipY = rect.position.y + rect.size.height;
            }

            this->tipPadding->setPaddings(tipY / ctx->getPixelScale(), 0, 0, tipX / ctx->getPixelScale());
        } else {
            if (tipPaddingIndex != -1) {
                stackElement->removeChild(tipPaddingIndex);
            }
        }

        return children;
    }
}
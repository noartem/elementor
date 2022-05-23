//
// Created by noartem on 22.05.2022.
//

#include "Scroll.h"

#include <climits>

namespace elementor {
    Scroll *scroll() {
        return new Scroll();
    }

    Scroll *Scroll::setScrollTop(float scrollTop) {
        this->scrollTop = scrollTop;
        return this;
    }

    float Scroll::getScrollTop() {
        return this->scrollTop;
    }

    Scroll *Scroll::setScrollLeft(float scrollLeft) {
        this->scrollLeft = scrollLeft;
        return this;
    }

    float Scroll::getScrollLeft() {
        return this->scrollLeft;
    }

    Scroll *Scroll::setScrollAcceleration(float scrollAcceleration) {
        this->scrollAcceleration = scrollAcceleration;
        return this;
    }

    float Scroll::getScrollAcceleration() {
        return this->scrollAcceleration;
    }

    Scroll *Scroll::setChild(Element *child) {
        child->context = this->context;
        this->updateChild(child);
        return this;
    }

    Size Scroll::getSize(Boundaries boundaries) {
        if (this->hasChild()) {
            Boundaries childBoundaries = {boundaries.min, {INT_MAX, INT_MAX}};
            this->childSize = this->getChild(this->context)->getSize(childBoundaries);
            return fitSizeInBoundaries(this->childSize, boundaries);
        } else {
            return boundaries.min;
        }
    }

    void Scroll::paintBackground(SkCanvas *canvas, ElementRect rect) {
        this->rect = rect;
    }

    std::vector <RenderElement> Scroll::getRenderChildren(Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild(this->context);

            int positionX = ceil(-1 * this->getScrollLeft() * this->context->monitorPixelScale);
            int positionY = ceil(-1 * this->getScrollTop() * this->context->monitorPixelScale);
            child.position = {positionX, positionY};
            child.size = this->childSize;

            children.push_back(child);
        }

        return children;
    }

    ClipBehavior Scroll::getClipBehaviour() {
        return ClipBehavior::AntiAlias;
    }

    EventCallbackResponse Scroll::onEvent(EventMouseMove *event) {
        this->hovered = this->rect.visibleContains(event->x, event->y);
        return EventCallbackResponse::None;
    }

    EventCallbackResponse Scroll::onEvent(EventScroll *event) {
        if (this->hovered) {
            this->scrollLeft -= event->xOffset * this->scrollAcceleration;
            float realScrollLeft = this->scrollLeft* this->context->monitorPixelScale;
            float maxScrollLeft = this->childSize.width - this->rect.size.width;
            float zero = 0.0;
            this->scrollLeft = std::min(std::max(realScrollLeft, zero), maxScrollLeft) / this->context->monitorPixelScale;

            this->scrollTop -= event->yOffset * this->scrollAcceleration;
            float realScrollTop = this->scrollTop * this->context->monitorPixelScale;
            float maxScrollTop = this->childSize.height - this->rect.size.height;
            this->scrollTop = std::min(std::max(realScrollTop, zero), maxScrollTop) / this->context->monitorPixelScale;
        }

        return EventCallbackResponse::None;
    }
}

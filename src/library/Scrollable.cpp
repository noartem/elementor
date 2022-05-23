//
// Created by noartem on 22.05.2022.
//

#include "Scrollable.h"

#include <climits>

namespace elementor {
    Scrollable *scrollable() {
        return new Scrollable();
    }

    Scrollable *Scrollable::setScrollableTop(float scrollableTop) {
        this->scrollableTop = scrollableTop;
        return this;
    }

    float Scrollable::getScrollableTop() {
        return this->scrollableTop;
    }

    Scrollable *Scrollable::setScrollableLeft(float scrollableLeft) {
        this->scrollableLeft = scrollableLeft;
        return this;
    }

    float Scrollable::getScrollableLeft() {
        return this->scrollableLeft;
    }

    Scrollable *Scrollable::setScrollableAcceleration(float scrollableAcceleration) {
        this->scrollableAcceleration = scrollableAcceleration;
        return this;
    }

    float Scrollable::getScrollableAcceleration() {
        return this->scrollableAcceleration;
    }

    Scrollable *Scrollable::setChild(Element *child) {
        child->context = this->context;
        this->updateChild(child);
        return this;
    }

    Size Scrollable::getSize(Boundaries boundaries) {
        if (this->hasChild()) {
            Boundaries childBoundaries = {boundaries.min, {INT_MAX, INT_MAX}};
            this->childSize = this->getChild(this->context)->getSize(childBoundaries);
            return fitSizeInBoundaries(this->childSize, boundaries);
        } else {
            return boundaries.min;
        }
    }

    void Scrollable::paintBackground(SkCanvas *canvas, ElementRect rect) {
        this->rect = rect;
    }

    std::vector <RenderElement> Scrollable::getRenderChildren(Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild(this->context);

            int positionX = ceil(-1 * this->getScrollableLeft() * this->context->monitorPixelScale);
            int positionY = ceil(-1 * this->getScrollableTop() * this->context->monitorPixelScale);
            child.position = {positionX, positionY};
            child.size = this->childSize;

            children.push_back(child);
        }

        return children;
    }

    ClipBehavior Scrollable::getClipBehaviour() {
        return ClipBehavior::AntiAlias;
    }

    EventCallbackResponse Scrollable::onEvent(EventMouseMove *event) {
        this->hovered = this->rect.visibleContains(event->x, event->y);
        return EventCallbackResponse::None;
    }

    EventCallbackResponse Scrollable::onEvent(EventScroll *event) {
        if (this->hovered) {
            this->scrollableLeft -= event->xOffset * this->scrollableAcceleration;
            float realScrollableLeft = this->scrollableLeft* this->context->monitorPixelScale;
            float maxScrollableLeft = this->childSize.width - this->rect.size.width;
            float zero = 0.0;
            this->scrollableLeft = std::min(std::max(realScrollableLeft, zero), maxScrollableLeft) / this->context->monitorPixelScale;

            this->scrollableTop -= event->yOffset * this->scrollableAcceleration;
            float realScrollableTop = this->scrollableTop * this->context->monitorPixelScale;
            float maxScrollableTop = this->childSize.height - this->rect.size.height;
            this->scrollableTop = std::min(std::max(realScrollableTop, zero), maxScrollableTop) / this->context->monitorPixelScale;
        }

        return EventCallbackResponse::None;
    }
}

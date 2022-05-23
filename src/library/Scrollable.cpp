//
// Created by noartem on 22.05.2022.
//

#include "Scrollable.h"

#include <climits>

namespace elementor {
    Scrollable *scrollable() {
        return new Scrollable();
    }

    Scrollable *Scrollable::setDirection(ScrollDirection direction) {
        this->direction = direction;
        return this;
    }

    ScrollDirection Scrollable::getDirection() {
        return this->direction;
    }

    Scrollable *Scrollable::setScrollTop(float scrollTop) {
        this->scrollTop = scrollTop;
        return this;
    }

    float Scrollable::getScrollTop() {
        return this->scrollTop;
    }

    Scrollable *Scrollable::setScrollLeft(float scrollLeft) {
        this->scrollLeft = scrollLeft;
        return this;
    }

    float Scrollable::getScrollLeft() {
        return this->scrollLeft;
    }

    Scrollable *Scrollable::setScrollAcceleration(float scrollAcceleration) {
        this->scrollAcceleration = scrollAcceleration;
        return this;
    }

    float Scrollable::getScrollAcceleration() {
        return this->scrollAcceleration;
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
            child.size = this->childSize;

            if (this->direction == ScrollDirection::Horizontal || this->direction == ScrollDirection::Both) {
                child.position.x = ceil(-1 * this->getScrollLeft() * this->context->monitorPixelScale);
            } else {
                child.position.x = 0;
            }

            if (this->direction == ScrollDirection::Vertical || this->direction == ScrollDirection::Both) {
                child.position.y = ceil(-1 * this->getScrollTop() * this->context->monitorPixelScale);
            } else {
                child.position.y = 0;
            }

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
            if (this->direction == ScrollDirection::Horizontal || this->direction == ScrollDirection::Both) {
                this->scrollLeft -= event->xOffset * this->scrollAcceleration;
                float realScrollLeft = this->scrollLeft* this->context->monitorPixelScale;
                float maxScrollLeft = this->childSize.width - this->rect.size.width;
                this->scrollLeft = std::min(std::max(realScrollLeft, (float) 0.0), maxScrollLeft) / this->context->monitorPixelScale;
            }

            if (this->direction == ScrollDirection::Vertical || this->direction == ScrollDirection::Both) {
                this->scrollTop -= event->yOffset * this->scrollAcceleration;
                float realScrollTop = this->scrollTop * this->context->monitorPixelScale;
                float maxScrollTop = this->childSize.height - this->rect.size.height;
                this->scrollTop = std::min(std::max(realScrollTop, (float) 0.0), maxScrollTop) / this->context->monitorPixelScale;
            }
        }

        return EventCallbackResponse::None;
    }
}

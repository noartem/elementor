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

    float Scrollable::getScrollHeight() {
        return this->childSize.height;
    }

    float Scrollable::getScrollWidth() {
        return this->childSize.width;
    }

    Scrollable *Scrollable::setScrollAcceleration(float scrollAcceleration) {
        this->scrollAcceleration = scrollAcceleration;
        return this;
    }

    float Scrollable::getScrollAcceleration() {
        return this->scrollAcceleration;
    }

    Scrollable *Scrollable::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Scrollable::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->hasChild()) {
            Boundaries childBoundaries = {boundaries.min, {INT_MAX, INT_MAX}};
            this->childSize = this->getChild()->getSize(ctx, childBoundaries);
            return fitSizeInBoundaries(this->childSize, boundaries);
        } else {
            return boundaries.min;
        }
    }

    void Scrollable::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        this->ctx = ctx;
        this->rect = rect;
    }

    std::vector <RenderElement> Scrollable::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.size = this->childSize;

            if (this->direction == ScrollDirection::Horizontal || this->direction == ScrollDirection::Both) {
                child.position.x = ceil(-1 * this->getScrollLeft() * ctx->monitorPixelScale);
            } else {
                child.position.x = 0;
            }

            if (this->direction == ScrollDirection::Vertical || this->direction == ScrollDirection::Both) {
                child.position.y = ceil(-1 * this->getScrollTop() * ctx->monitorPixelScale);
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
                float realScrollLeft = this->scrollLeft * this->ctx->monitorPixelScale;
                float maxScrollLeft = this->childSize.width - this->rect.size.width;
                this->scrollLeft = std::min(std::max(realScrollLeft, (float) 0.0), maxScrollLeft) / this->ctx->monitorPixelScale;
            }

            if (this->direction == ScrollDirection::Vertical || this->direction == ScrollDirection::Both) {
                this->scrollTop -= event->yOffset * this->scrollAcceleration;
                float realScrollTop = this->scrollTop * this->ctx->monitorPixelScale;
                float maxScrollTop = this->childSize.height - this->rect.size.height;
                this->scrollTop = std::min(std::max(realScrollTop, (float) 0.0), maxScrollTop) / this->ctx->monitorPixelScale;
            }
        }

        return EventCallbackResponse::None;
    }
}

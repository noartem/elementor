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

    bool Scrollable::isHorizontalScroll() {
        return this->getDirection() == ScrollDirection::Horizontal || this->getDirection() == ScrollDirection::Both;
    }

    bool Scrollable::isVerticalScroll() {
        return this->getDirection() == ScrollDirection::Vertical || this->getDirection() == ScrollDirection::Both;
    }

    float Scrollable::getHeight() {
        return this->rect.size.height / this->ctx->monitorPixelScale;
    }

    float Scrollable::getWidth() {
        return this->rect.size.width / this->ctx->monitorPixelScale;
    }

    float Scrollable::getMaxScrollLeft() {
        return std::max(this->childSize.width - this->rect.size.width, 0) / this->ctx->monitorPixelScale;
    }

    float Scrollable::getMaxScrollTop() {
        return std::max(this->childSize.height - this->rect.size.height, 0) / this->ctx->monitorPixelScale;
    }

    Scrollable *Scrollable::setScrollLeft(float scrollLeft) {
        this->scrollLeft = std::min(std::max(scrollLeft, (float) 0), this->getMaxScrollLeft());
        return this;
    }

    Scrollable *Scrollable::setScrollTop(float scrollTop) {
        this->scrollTop = std::min(std::max(scrollTop, (float) 0), this->getMaxScrollTop());
        return this;
    }

    float Scrollable::getScrollTop() {
        return this->scrollTop;
    }

    float Scrollable::getScrollLeft() {
        return this->scrollLeft;
    }

    float Scrollable::getScrollHeight() {
        if (this->childSize.height == 0) {
            return 0;
        } else {
            return this->childSize.height / this->ctx->monitorPixelScale;
        }
    }

    float Scrollable::getScrollWidth() {
        if (this->childSize.width == 0) {
            return 0;
        } else {
            return this->childSize.width / this->ctx->monitorPixelScale;
        }
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

    Size Scrollable::getChildSize(ApplicationContext *ctx, Boundaries boundaries) {
        Boundaries childBoundaries = {{0, 0}, {INT_MAX, INT_MAX}};
        if (this->direction == ScrollDirection::Horizontal) {
            childBoundaries.min.height = boundaries.max.height;
            childBoundaries.max.height = boundaries.max.height;
        } else if (this->direction == ScrollDirection::Vertical) {
            childBoundaries.min.width = boundaries.max.width;
            childBoundaries.max.width = boundaries.max.width;
        }

        return this->getChild()->getSize(ctx, childBoundaries);
    }

    Size Scrollable::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->hasChild()) {
            return fitSizeInBoundaries(this->getChildSize(ctx, boundaries), boundaries);
        } else {
            return boundaries.min;
        }
    }

    void Scrollable::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        ElementRect oldRect = this->rect;

        this->ctx = ctx;
        this->rect = rect;
        this->childSize = this->getChildSize(ctx, {rect.size, rect.size});

        if (rect.size.height != oldRect.size.height || rect.size.width != oldRect.size.width) {
            if (this->isHorizontalScroll()) {
                if (rect.size.width + this->getScrollLeft() > this->childSize.width) {
                    this->scrollLeft = std::max(this->childSize.width - rect.size.width, 0);
                }
            }

            if (this->isVerticalScroll()) {
                if (rect.size.height + this->getScrollTop() > this->childSize.height) {
                    this->scrollTop = std::max(this->childSize.height - rect.size.height, 0);
                }
            }
        }
    }

    std::vector <RenderElement> Scrollable::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.size = this->childSize;
            child.position.x = ceil(-1 * this->getScrollLeft() * ctx->monitorPixelScale);
            child.position.y = ceil(-1 * this->getScrollTop() * ctx->monitorPixelScale);

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
            if (event->xOffset != 0 && this->isHorizontalScroll()) {
                int maxScrollLeft = ceil(this->getMaxScrollLeft() * this->ctx->monitorPixelScale);
                int realScrollLeft = ceil(this->getScrollLeft() * this->ctx->monitorPixelScale);
                if (event->xOffset < 0 && realScrollLeft == maxScrollLeft || event->xOffset > 0 && realScrollLeft == 0) {
                    return EventCallbackResponse::None;
                } else {
                    int scrollLeftChaned = realScrollLeft - ceil(event->xOffset * this->scrollAcceleration * this->ctx->monitorPixelScale);
                    this->scrollLeft = std::min(std::max(scrollLeftChaned, 0), maxScrollLeft) / this->ctx->monitorPixelScale;
                }
            }

            if (event->yOffset != 0 && this->isVerticalScroll()) {
                int maxScrollTop = ceil(this->getMaxScrollTop() * this->ctx->monitorPixelScale);
                int realScrollTop = ceil(this->getScrollTop() * this->ctx->monitorPixelScale);
                if (event->yOffset < 0 && realScrollTop == maxScrollTop || event->yOffset > 0 && realScrollTop == 0) {
                    return EventCallbackResponse::None;
                } else {
                    int scrollTopChaned = realScrollTop - ceil(event->yOffset * this->scrollAcceleration * this->ctx->monitorPixelScale);
                    this->scrollTop = std::min(std::max(scrollTopChaned, 0), maxScrollTop) / this->ctx->monitorPixelScale;
                }
            }

            return EventCallbackResponse::StopPropagation;
        }

        return EventCallbackResponse::None;
    }
}

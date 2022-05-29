//
// Created by noartem on 22.05.2022.
//

#include "Scrollable.h"

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

    float Scrollable::getMonitorPixelScale() {
        if (this->ctx) {
            return this->ctx->monitorPixelScale;
        } else {
            return 1;
        }
    }

    float Scrollable::getHeight() {
        return this->rect.size.height / this->getMonitorPixelScale();
    }

    float Scrollable::getWidth() {
        return this->rect.size.width / this->getMonitorPixelScale();
    }

    float Scrollable::getMaxScrollLeft() {
        return std::max(this->childSize.width - this->rect.size.width, 0) / this->getMonitorPixelScale();
    }

    float Scrollable::getMaxScrollTop() {
        return std::max(this->childSize.height - this->rect.size.height, 0) / this->getMonitorPixelScale();
    }

    Scrollable *Scrollable::setScrollLeft(float scrollLeft) {
        this->scrollLeft = std::min(std::max(scrollLeft, ZERO), this->getMaxScrollLeft());
        return this;
    }

    Scrollable *Scrollable::setScrollTop(float scrollTop) {
        this->scrollTop = std::min(std::max(scrollTop, ZERO), this->getMaxScrollTop());
        return this;
    }

    float Scrollable::getScrollTop() {
        return this->scrollTop;
    }

    float Scrollable::getScrollLeft() {
        return this->scrollLeft;
    }

    float Scrollable::getScrollHeight() {
        return this->childSize.height / this->getMonitorPixelScale();
    }

    float Scrollable::getScrollWidth() {
        return this->childSize.width / this->getMonitorPixelScale();
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
        Boundaries childBoundaries = {boundaries.min, {INF, INF}};
        if (this->direction == ScrollDirection::Horizontal) {
            childBoundaries.max.height = boundaries.max.height;
        } else if (this->direction == ScrollDirection::Vertical) {
            childBoundaries.max.width = boundaries.max.width;
        }

        return this->getChild()->getSize(ctx, childBoundaries);
    }

    Size Scrollable::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        return boundaries.max;
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
            this->childSize = this->getChildSize(ctx, {rect.size, rect.size});
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
                int maxScrollLeft = ceil(this->getMaxScrollLeft() * this->getMonitorPixelScale());
                int scrollLeft = ceil(this->getScrollLeft() * this->getMonitorPixelScale());
                if (event->xOffset < 0 && scrollLeft == maxScrollLeft || event->xOffset > 0 && scrollLeft == 0) {
                    return EventCallbackResponse::None;
                } else {
                    int scrollLeftChaned = scrollLeft - ceil(event->xOffset * this->scrollAcceleration * this->getMonitorPixelScale());
                    this->scrollLeft = std::min(std::max(scrollLeftChaned, 0), maxScrollLeft) / this->getMonitorPixelScale();
                }
            }

            if (event->yOffset != 0 && this->isVerticalScroll()) {
                int maxScrollTop = ceil(this->getMaxScrollTop() * this->getMonitorPixelScale());
                int scrollTop = ceil(this->getScrollTop() * this->getMonitorPixelScale());
                if (event->yOffset < 0 && scrollTop == maxScrollTop || event->yOffset > 0 && scrollTop == 0) {
                    return EventCallbackResponse::None;
                } else {
                    int scrollTopChaned = scrollTop - ceil(event->yOffset * this->scrollAcceleration * this->getMonitorPixelScale());
                    this->scrollTop = std::min(std::max(scrollTopChaned, 0), maxScrollTop) / this->getMonitorPixelScale();
                }
            }

            return EventCallbackResponse::StopPropagation;
        }

        return EventCallbackResponse::None;
    }
}

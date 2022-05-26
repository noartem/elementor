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
            if (this->direction == ScrollDirection::Horizontal || this->direction == ScrollDirection::Both) {
                if (rect.size.width + this->getScrollLeft() > this->childSize.width) {
                    this->scrollLeft = std::max(this->childSize.width - rect.size.width, 0);
                }
            }

            if (this->direction == ScrollDirection::Vertical || this->direction == ScrollDirection::Both) {
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
            if (event->xOffset != 0 && (this->direction == ScrollDirection::Horizontal || this->direction == ScrollDirection::Both)) {
                int maxScrollLeft = std::max(this->childSize.width - this->rect.size.width, 0);
                int realScrollLeft = ceil(this->getScrollLeft() * this->ctx->monitorPixelScale);
                if (event->xOffset < 0 && realScrollLeft == maxScrollLeft || event->xOffset > 0 && realScrollLeft == 0) {
                    return EventCallbackResponse::None;
                } else {
                    int scrollLeftChaned = realScrollLeft - ceil(event->xOffset * this->scrollAcceleration * this->ctx->monitorPixelScale);
                    this->scrollLeft = std::min(std::max(scrollLeftChaned, 0), maxScrollLeft) / this->ctx->monitorPixelScale;
                }
            }

            if (event->yOffset != 0 && (this->direction == ScrollDirection::Vertical || this->direction == ScrollDirection::Both)) {
                int maxScrollTop = std::max(this->childSize.height - this->rect.size.height, 0);
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

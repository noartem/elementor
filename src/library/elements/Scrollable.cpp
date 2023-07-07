//
// Created by noartem on 22.05.2022.
//

#include "Scrollable.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<Scrollable> scrollable() {
        return std::make_shared<Scrollable>();
    }

    std::shared_ptr<Scrollable> Scrollable::setDirection(ScrollDirection newDirection) {
        this->direction = newDirection;
        return shared_from_this();
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

    float Scrollable::getHeight() const {
        return this->rect.size.height;
    }

    float Scrollable::getWidth() const {
        return this->rect.size.width;
    }

    float Scrollable::getMaxScrollLeft() const {
        return std::max(this->childSize.width - this->rect.size.width, ZERO);
    }

    float Scrollable::getMaxScrollTop() const {
        return std::max(this->childSize.height - this->rect.size.height, ZERO);
    }

    std::shared_ptr<Scrollable> Scrollable::setScrollLeft(float newScrollLeft) {
        this->scrollLeft = std::min(std::max(newScrollLeft, ZERO), this->getMaxScrollLeft());
        return shared_from_this();
    }

    std::shared_ptr<Scrollable> Scrollable::setScrollTop(float newScrollTop) {
        this->scrollTop = std::min(std::max(newScrollTop, ZERO), this->getMaxScrollTop());
        return shared_from_this();
    }

    float Scrollable::getScrollTop() const {
        return this->scrollTop;
    }

    float Scrollable::getScrollLeft() const {
        return this->scrollLeft;
    }

    float Scrollable::getScrollHeight() const {
        return this->childSize.height;
    }

    float Scrollable::getScrollWidth() const {
        return this->childSize.width;
    }

    std::shared_ptr<Scrollable> Scrollable::setScrollAcceleration(float newScrollAcceleration) {
        this->scrollAcceleration = newScrollAcceleration;
        return shared_from_this();
    }

    float Scrollable::getScrollAcceleration() const {
        return this->scrollAcceleration;
    }

    std::shared_ptr<Scrollable> Scrollable::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size Scrollable::getChildSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        Boundaries childBoundaries = {boundaries.min, {INFINITY, INFINITY}};
        if (this->direction == ScrollDirection::Horizontal) {
            childBoundaries.max.height = boundaries.max.height;
        } else if (this->direction == ScrollDirection::Vertical) {
            childBoundaries.max.width = boundaries.max.width;
        }

        return this->getChild()->getSize(std::move(ctx), std::move(window), childBoundaries);
    }

    Size Scrollable::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        this->childSize = this->getChildSize(ctx, window, boundaries);
        return fitSizeInBoundaries(this->childSize, boundaries);
    }

    void Scrollable::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) {
        ElementRect oldRect = this->rect;
        this->rect = rect;

        if (rect.size.height != oldRect.size.height || rect.size.width != oldRect.size.width) {
            if (this->isHorizontalScroll()) {
                if (rect.size.width + this->getScrollLeft() > this->childSize.width) {
                    this->scrollLeft = std::min(std::max(this->childSize.width - rect.size.width, ZERO),
                                                this->getMaxScrollLeft());
                }
            }

            if (this->isVerticalScroll()) {
                if (rect.size.height + this->getScrollTop() > this->childSize.height) {
                    this->scrollTop = std::min(std::max(this->childSize.height - rect.size.height, ZERO),
                                               this->getMaxScrollTop());
                }
            }
        }
    }

    std::vector<RenderElement> Scrollable::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector<RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{};
            childElement.element = this->getChild();
            this->childSize = this->getChildSize(ctx, window, {{0, 0}, rect.size});
            childElement.size = this->childSize;
            childElement.position.x = -1 * this->getScrollLeft();
            childElement.position.y = -1 * this->getScrollTop();

            children.push_back(childElement);
        }

        return children;
    }

    ClipBehavior Scrollable::getClipBehaviour() {
        return ClipBehavior::AntiAlias;
    }

    EventCallbackResponse Scrollable::onEvent(std::shared_ptr<EventHover> event) {
        this->hovered = event->hovered;
        return EventCallbackResponse::None;
    }

    EventCallbackResponse Scrollable::onEvent(std::shared_ptr<EventScroll> event) {
        if (this->hovered) {
            if (event->xOffset != 0 && this->isHorizontalScroll()) {
                float scrollLeft = this->getScrollLeft();
                float maxScrollLeft = this->getMaxScrollLeft();
                if (event->xOffset < 0 && scrollLeft == maxScrollLeft || event->xOffset > 0 && scrollLeft == 0) {
                    return EventCallbackResponse::None;
                } else {
                    this->scrollLeft = std::min(std::max(scrollLeft - event->xOffset * this->scrollAcceleration, ZERO),
                                                maxScrollLeft);
                }
            }

            if (event->yOffset != 0 && this->isVerticalScroll()) {
                float scrollTop = this->getScrollTop();
                float maxScrollTop = this->getMaxScrollTop();
                if (event->yOffset < 0 && scrollTop == maxScrollTop || event->yOffset > 0 && scrollTop == 0) {
                    return EventCallbackResponse::None;
                } else {
                    this->scrollTop = std::min(std::max(scrollTop - event->yOffset * this->scrollAcceleration, ZERO),
                                               maxScrollTop);
                }
            }

            return EventCallbackResponse::StopPropagation;
        }

        return EventCallbackResponse::None;
    }
}

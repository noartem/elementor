//
// Created by noartem on 21.05.2022.
//

#include "Clickable.h"

namespace elementor {
    Clickable *clickable() {
        return new Clickable();
    }

    Clickable *Clickable::onButton(std::function<EventCallbackResponse (EventMouseButton *event)> callback) {
        this->callbackButton = callback;
        return this;
    }

    Clickable *Clickable::onButton(std::function<void (EventMouseButton *event)> callback) {
        this->callbackButton = [callback](EventMouseButton *event) {
            callback(event);
            return EventCallbackResponse::None;
        };
        return this;
    }

    Clickable *Clickable::onClick(std::function<EventCallbackResponse ()> callback) {
        this->callbackClick = callback;
        return this;
    }

    Clickable *Clickable::onClick(std::function<void ()> callback) {
        this->callbackClick = [callback]() {
            callback();
            return EventCallbackResponse::None;
        };
        return this;
    }

    Clickable *Clickable::onRightClick(std::function<EventCallbackResponse ()> callback) {
        this->callbackRightClick = callback;
        return this;
    }

    Clickable *Clickable::onRightClick(std::function<void ()> callback) {
        this->callbackRightClick = [callback]() {
            callback();
            return EventCallbackResponse::None;
        };
        return this;
    }

    Clickable *Clickable::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Clickable::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Clickable::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        this->rect = rect;
    }

    std::vector <RenderElement> Clickable::getRenderChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.position = {0, 0};
            child.size = size;

            children.push_back(child);
        }

        return children;
    }

    EventCallbackResponse Clickable::onEvent(EventMouseMove *event) {
        this->hovered = this->rect.visibleContains(event->x, event->y);
        return EventCallbackResponse::None;
    }

    EventCallbackResponse Clickable::onEvent(EventMouseButton *event) {
        if (this->hovered) {
            if (this->callbackButton) {
                EventCallbackResponse callbackResponse = this->callbackButton(event);
                if (callbackResponse != EventCallbackResponse::None) {
                    return callbackResponse;
                }
            }

            if (event->action == MouseAction::Press && event->button == MouseButton::Left && this->callbackClick) {
                EventCallbackResponse callbackResponse = this->callbackClick();
                if (callbackResponse != EventCallbackResponse::None) {
                    return callbackResponse;
                }
            }

            if (event->action == MouseAction::Press && event->button == MouseButton::Right && this->callbackRightClick) {
                EventCallbackResponse callbackResponse = this->callbackRightClick();
                if (callbackResponse != EventCallbackResponse::None) {
                    return callbackResponse;
                }
            }
        }

        return EventCallbackResponse::None;
    }
}

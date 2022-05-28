//
// Created by noartem on 21.05.2022.
//

#include "Clickable.h"

namespace elementor {
    Clickable *clickable() {
        return new Clickable();
    }

    Clickable *Clickable::onButton(std::function<EventCallbackResponse (EventMouseButton *event, Position position)> callback) {
        this->callbackButton = callback;
        return this;
    }

    Clickable *Clickable::onButton(std::function<void ()> callback) {
        this->callbackButton = [callback] (EventMouseButton *event, Position position) {
            callback();
            return EventCallbackResponse::None;
        };
        return this;
    }

    Clickable *Clickable::onClick(std::function<EventCallbackResponse (EventMouseButton *event, Position position)> callback) {
        this->callbackClick = callback;
        return this;
    }

    Clickable *Clickable::onClick(std::function<void ()> callback) {
        this->callbackClick = [callback] (EventMouseButton *event, Position position) {
            callback();
            return EventCallbackResponse::None;
        };
        return this;
    }

    Clickable *Clickable::onRightClick(std::function<EventCallbackResponse (EventMouseButton *event, Position position)> callback) {
        this->callbackRightClick = callback;
        return this;
    }

    Clickable *Clickable::onRightClick(std::function<void ()> callback) {
        this->callbackRightClick = [callback] (EventMouseButton *event, Position position) {
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

    std::vector <RenderElement> Clickable::getChildren(ApplicationContext *ctx, Size size) {
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
        Position cursorPosition = {(int) event->x, (int) event->y};
        this->hovered = this->rect.visibleContains(cursorPosition);
        this->cursorPosition = this->rect.absolutePositionToContained(cursorPosition);
        return EventCallbackResponse::None;
    }

    EventCallbackResponse Clickable::onEvent(EventMouseButton *event) {
        if (this->hovered) {
            if (this->callbackButton) {
                EventCallbackResponse callbackResponse = this->callbackButton(event, this->cursorPosition);
                if (callbackResponse != EventCallbackResponse::None) {
                    return callbackResponse;
                }
            }

            if (event->action == MouseAction::Press && event->button == MouseButton::Left && this->callbackClick) {
                EventCallbackResponse callbackResponse = this->callbackClick(event, this->cursorPosition);
                if (callbackResponse != EventCallbackResponse::None) {
                    return callbackResponse;
                }
            }

            if (event->action == MouseAction::Press && event->button == MouseButton::Right && this->callbackRightClick) {
                EventCallbackResponse callbackResponse = this->callbackRightClick(event, this->cursorPosition);
                if (callbackResponse != EventCallbackResponse::None) {
                    return callbackResponse;
                }
            }
        }

        return EventCallbackResponse::None;
    }
}

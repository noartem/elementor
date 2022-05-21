//
// Created by noartem on 21.05.2022.
//

#include "Clickable.h"

namespace elementor {
    Clickable *clickable() {
        return new Clickable();
    }

    Clickable::Clickable() {
        this->hoverable = new Hoverable();
        this->hoverable->onEnter([this]() { this->hovered = true; });
        this->hoverable->onLeave([this]() { this->hovered = false; });
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
        this->hoverable->context = this->context;
        this->hoverable->setChild(child);
        return this;
    }

    Hoverable *Clickable::getChild() {
        this->hoverable->context = this->context;
        return this->hoverable;
    }

    Size Clickable::getSize(Boundaries boundaries) {
        return this->getChild()->getSize(boundaries);
    }

    std::vector <RenderElement> Clickable::getRenderChildren(Size size) {
        RenderElement child;
        child.element = this->getChild();
        child.position = {0, 0};
        child.size = size;

        return {child};
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

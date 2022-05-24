//
// Created by noartem on 18.05.2022.
//

#include "Hoverable.h"

namespace elementor {
    Hoverable *hoverable() {
        return new Hoverable();
    }

    Hoverable *Hoverable::onEnter(std::function<EventCallbackResponse (EventMouseMove *event)> callback) {
        this->callbackEnter = callback;
        return this;
    }

    Hoverable *Hoverable::onEnter(std::function<void ()> callback) {
        this->callbackEnter = [callback](EventMouseMove *event) {
            callback();
            return EventCallbackResponse::None;
        };
        return this;
    }

    Hoverable *Hoverable::onMove(std::function<EventCallbackResponse (EventMouseMove *event)> callback) {
        this->callbackMove = callback;
        return this;
    }

    Hoverable *Hoverable::onMove(std::function<void ()> callback) {
        this->callbackMove = [callback](EventMouseMove *event) {
            callback();
            return EventCallbackResponse::None;
        };
        return this;
    }

    Hoverable *Hoverable::onLeave(std::function<EventCallbackResponse (EventMouseMove *event)> callback) {
        this->callbackLeave = callback;
        return this;
    }

    Hoverable *Hoverable::onLeave(std::function<void ()> callback) {
        this->callbackLeave = [callback](EventMouseMove *event) {
            callback();
            return EventCallbackResponse::None;
        };
        return this;
    }

    Hoverable *Hoverable::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Hoverable::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Hoverable::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        this->rect = rect;
    }

    std::vector <RenderElement> Hoverable::getChildren(ApplicationContext *ctx, Size size) {
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

    EventCallbackResponse Hoverable::onEvent(EventMouseMove *event) {
        if (this->rect.visibleContains(event->x, event->y)) {
            if (this->hovered) {
                if (this->callbackMove) {
                    EventCallbackResponse callbackResponse = this->callbackMove(event);
                    if (callbackResponse != EventCallbackResponse::None) {
                        return callbackResponse;
                    }
                }
            } else {
                this->hovered = true;
                if (this->callbackEnter) {
                    EventCallbackResponse callbackResponse = this->callbackEnter(event);
                    if (callbackResponse != EventCallbackResponse::None) {
                        return callbackResponse;
                    }
                }
            }
        } else if (this->hovered) {
            this->hovered = false;
            if (this->callbackLeave) {
                EventCallbackResponse callbackResponse = this->callbackLeave(event);
                if (callbackResponse != EventCallbackResponse::None) {
                    return callbackResponse;
                }
            }
        }

        return EventCallbackResponse::None;
    }
}

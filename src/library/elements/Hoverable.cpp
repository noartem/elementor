//
// Created by noartem on 18.05.2022.
//

#include "Hoverable.h"

#include <utility>

namespace elementor::elements {
    Hoverable *hoverable() {
        return new Hoverable();
    }

    Hoverable *Hoverable::onEnter(std::function<EventCallbackResponse (EventMouseMove *event)> callback) {
        this->callbackEnter = std::move(callback);
        return this;
    }

    Hoverable *Hoverable::onEnter(const std::function<void ()>& callback) {
        this->callbackEnter = [callback](EventMouseMove *event) {
            callback();
            return EventCallbackResponse::None;
        };
        return this;
    }

    Hoverable *Hoverable::onMove(std::function<EventCallbackResponse (EventMouseMove *event)> callback) {
        this->callbackMove = std::move(callback);
        return this;
    }

    Hoverable *Hoverable::onMove(const std::function<void ()>& callback) {
        this->callbackMove = [callback](EventMouseMove *event) {
            callback();
            return EventCallbackResponse::None;
        };
        return this;
    }

    Hoverable *Hoverable::onLeave(std::function<EventCallbackResponse (EventMouseMove *event)> callback) {
        this->callbackLeave = std::move(callback);
        return this;
    }

    Hoverable *Hoverable::onLeave(const std::function<void ()>& callback) {
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

    Size Hoverable::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Hoverable::paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) {
        this->rect = rect;
    }

    std::vector <RenderElement> Hoverable::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
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

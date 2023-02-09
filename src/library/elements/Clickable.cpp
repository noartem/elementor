//
// Created by noartem on 21.05.2022.
//

#include "Clickable.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<Clickable> clickable() {
        return std::make_shared<Clickable>();
    }

    std::shared_ptr<Clickable> Clickable::onButton(
            std::function<EventCallbackResponse(std::shared_ptr<EventMouseButton> event, Position position)> callback) {
        this->callbackButton = std::move(callback);
        return shared_from_this();
    }

    std::shared_ptr<Clickable> Clickable::onButton(const std::function<void()> &callback) {
        this->callbackButton = [callback](const std::shared_ptr<EventMouseButton> &event, Position position) {
            callback();
            return EventCallbackResponse::None;
        };
        return shared_from_this();
    }

    std::shared_ptr<Clickable> Clickable::onClick(
            std::function<EventCallbackResponse(std::shared_ptr<EventMouseButton> event, Position position)> callback) {
        this->callbackClick = std::move(callback);
        return shared_from_this();
    }

    std::shared_ptr<Clickable> Clickable::onClick(const std::function<void()> &callback) {
        this->callbackClick = [callback](const std::shared_ptr<EventMouseButton> &event, Position position) {
            callback();
            return EventCallbackResponse::None;
        };
        return shared_from_this();
    }

    std::shared_ptr<Clickable> Clickable::onRightClick(
            std::function<EventCallbackResponse(std::shared_ptr<EventMouseButton> event, Position position)> callback) {
        this->callbackRightClick = std::move(callback);
        return shared_from_this();
    }

    std::shared_ptr<Clickable> Clickable::onRightClick(const std::function<void()> &callback) {
        this->callbackRightClick = [callback](const std::shared_ptr<EventMouseButton> &event, Position position) {
            callback();
            return EventCallbackResponse::None;
        };
        return shared_from_this();
    }

    std::shared_ptr<Clickable> Clickable::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size
    Clickable::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Clickable::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                                    SkCanvas *canvas, ElementRect rect) {
        this->window = window;
        this->rect = rect;
    }

    std::vector<RenderElement>
    Clickable::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector<RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }

    EventCallbackResponse Clickable::onEvent(std::shared_ptr<EventMouseMove> event) {
        this->hovered = this->rect.visibleContains({event->x, event->y});
        this->cursorPosition = this->rect.absolutePositionToContained(cursorPosition);
        return EventCallbackResponse::None;
    }

    EventCallbackResponse Clickable::onEvent(std::shared_ptr<EventMouseMoving> event) {
        this->hovered = false;
        return EventCallbackResponse::None;
    }

    EventCallbackResponse Clickable::onEvent(std::shared_ptr<EventMouseButton> event) {
        if (this->hovered) {
            if (this->callbackButton) {
                EventCallbackResponse callbackResponse = this->callbackButton(event, this->cursorPosition);
                if (callbackResponse != EventCallbackResponse::None) {
                    return callbackResponse;
                }
            }

            if (event->action == KeyAction::Press && event->button == MouseButton::Left && this->callbackClick) {
                EventCallbackResponse callbackResponse = this->callbackClick(event, this->cursorPosition);
                if (callbackResponse != EventCallbackResponse::None) {
                    return callbackResponse;
                }
            }

            if (event->action == KeyAction::Press && event->button == MouseButton::Right && this->callbackRightClick) {
                EventCallbackResponse callbackResponse = this->callbackRightClick(event, this->cursorPosition);
                if (callbackResponse != EventCallbackResponse::None) {
                    return callbackResponse;
                }
            }
        }

        return EventCallbackResponse::None;
    }
}

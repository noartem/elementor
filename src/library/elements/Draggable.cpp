//
// Created by noartem on 21.05.2022.
//

#include "Draggable.h"

namespace elementor::elements {
    Draggable *draggable() {
        return new Draggable();
    }

    Draggable *Draggable::onStart(std::function<bool (Position position, Position absolutePosition)> callback) {
        this->callbackStart = callback;
        return this;
    }

    Draggable *Draggable::onStart(std::function<void ()> callback) {
        this->callbackStart = [callback] (Position position, Position absolutePosition) {
            callback();
            return true;
        };
        return this;
    }

    Draggable *Draggable::onEnd(std::function<void (Position position, Position absolutePosition)> callback) {
        this->callbackEnd = callback;
        return this;
    }

    Draggable *Draggable::onEnd(std::function<void ()> callback) {
        this->callbackEnd = [callback] (Position position, Position absolutePosition) {
            callback();
        };
        return this;
    }

    Draggable *Draggable::onMove(std::function<void (Position position, Position absolutePosition, Position diff)> callback) {
        this->callbackMove = callback;
        return this;
    }

    Draggable *Draggable::onMove(std::function<void ()> callback) {
        this->callbackMove = [callback] (Position position, Position absolutePosition, Position diff) {
            callback();
        };
        return this;
    }

    Draggable *Draggable::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Draggable::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Draggable::paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) {
        this->rect = rect;
    }

    std::vector <RenderElement> Draggable::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }

    EventCallbackResponse Draggable::onEvent(EventMouseMove *event) {
        this->previousCursorAbsolutePosition = this->cursorAbsolutePosition;
        this->cursorAbsolutePosition = {event->x, event->y};
        this->hovered = this->rect.visibleContains(this->cursorAbsolutePosition);
        this->cursorPosition = this->rect.absolutePositionToContained(this->cursorAbsolutePosition);

        if (this->dragging && this->callbackMove) {
            Position cursorPositionDiff = {
                this->cursorAbsolutePosition.x - this->previousCursorAbsolutePosition.x,
                this->cursorAbsolutePosition.y - this->previousCursorAbsolutePosition.y,
            };
            this->callbackMove(this->cursorPosition, this->cursorAbsolutePosition, cursorPositionDiff);
        }

        return EventCallbackResponse::None;
    }

    EventCallbackResponse Draggable::onEvent(EventMouseButton *event) {
        if (this->hovered && !this->dragging && event->action == KeyAction::Press && event->button == MouseButton::Left) {
            if (this->callbackStart) {
                bool startAllowed = this->callbackStart(this->cursorPosition, this->cursorAbsolutePosition);
                if (!startAllowed) {
                    return EventCallbackResponse::None;
                }
            }

            this->dragging = true;

            return EventCallbackResponse::StopPropagation;
        }

        if (this->dragging && event->action == KeyAction::Release && event->button == MouseButton::Left) {
            if (this->callbackEnd) {
                this->callbackEnd(this->cursorPosition, this->cursorAbsolutePosition);
            }

            this->dragging = false;

            return EventCallbackResponse::StopPropagation;
        }

        return EventCallbackResponse::None;
    }
}

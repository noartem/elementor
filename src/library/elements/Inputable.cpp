//
// Created by noartem on 28.06.2022.
//

#include "Inputable.h"

namespace elementor::elements {
    Inputable *inputable() {
        return new Inputable();
    }

    Inputable *Inputable::onChange(std::function<std::string (std::string value)> callback) {
        this->callbackChange = callback;
        return this;
    }

    Inputable *Inputable::onChange(std::function<void (std::string value)> callback) {
        this->callbackChange = [callback] (std::string value) {
            callback(value);
            return value;
        };
        return this;
    }

    Inputable *Inputable::onFocus(std::function<void ()> callback) {
        this->callbackFocus = callback;
        return this;
    }

    Inputable *Inputable::onBlur(std::function<void ()> callback) {
        this->callbackBlur = callback;
        return this;
    }

    Inputable *Inputable::setText(std::string text) {
        this->text = text;
        return this;
    }

    std::string Inputable::getText() {
        return this->text;
    }

    Inputable *Inputable::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Inputable::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Inputable::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        this->rect = rect;
    }

    std::vector <RenderElement> Inputable::getChildren(ApplicationContext *ctx, Size size) {
        RenderElement child;
        child.element = this->getChild();
        child.position = {0, 0};
        child.size = size;
        return {child};
    }

    EventCallbackResponse Inputable::onEvent(EventMouseMove *event) {
        Position cursorPosition = {event->x, event->y};
        this->hovered = this->rect.visibleContains(cursorPosition);
        return EventCallbackResponse::None;
    }

    EventCallbackResponse Inputable::onEvent(EventMouseButton *event) {
        if (this->hovered) {
            if (event->action == Action::Press && event->button == MouseButton::Left) {
                this->focused = true;
                if (this->callbackFocus) {
                    this->callbackFocus();
                }
            }
        } else {
            this->focused = false;
            if (this->callbackBlur) {
                this->callbackBlur();
            }
        }

        return EventCallbackResponse::None;
    }

    EventCallbackResponse Inputable::onEvent(EventKeyboard *event) {
        if (this->focused) {
            if (event->key == KeyboardKey::Escape) {
                this->focused = false;
            }

            // ... text input

            return EventCallbackResponse::StopPropagation;
        }

        return EventCallbackResponse::None;
    }
}

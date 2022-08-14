//
// Created by noartem on 28.06.2022.
//

#include "Inputable.h"
#include "../String.h"

namespace elementor::elements {
    Inputable *inputable() {
        return new Inputable();
    }

    Inputable *Inputable::onChange(std::function<std::u32string (std::u32string value)> callback) {
        this->callbackChange = callback;
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

    Inputable *Inputable::setText(std::u32string text) {
        this->text = text;

        if (this->callbackChange) {
            this->callbackChange(this->text);
        }

        return this;
    }

    Inputable *Inputable::setText(std::string text) {
        std::u32string textU32;
        fromUTF8(text, textU32);
        return this->setText(textU32);
    }

    std::u32string Inputable::getText() {
        return this->text;
    }

    Inputable *Inputable::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Inputable::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Inputable::paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) {
        this->rect = rect;
    }

    std::vector <RenderElement> Inputable::getChildren(ApplicationContext *ctx, Window *window, Size size) {
        this->ctx = ctx;
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
            if (event->action == KeyAction::Press && event->button == MouseButton::Left) {
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
        if (this->focused && (event->action == KeyAction::Press || event->action == KeyAction::Repeat)) {
            if (event->key == KeyboardKey::Escape) {
                this->focused = false;
                if (this->callbackBlur) {
                    this->callbackBlur();
                }
                return EventCallbackResponse::StopPropagation;
            }

            if (event->key == KeyboardKey::C && event->mod == KeyMod::Control) {
                this->ctx->clipboard->set(toUTF8(this->text));
                return EventCallbackResponse::StopPropagation;
            }

            if (event->key == KeyboardKey::V && event->mod == KeyMod::Control) {
                std::string clipboardValueU8 = this->ctx->clipboard->get();
                std::u32string clipboardValueU32;
                fromUTF8(clipboardValueU8, clipboardValueU32);
                this->text += clipboardValueU32;
                if (this->callbackChange) {
                    this->text = this->callbackChange(this->text);
                }
                return EventCallbackResponse::StopPropagation;
            }

            if (event->key == KeyboardKey::Backspace && this->text.size() > 0) {
                this->text.pop_back();
                if (this->callbackChange) {
                    this->text = this->callbackChange(this->text);
                }
                return EventCallbackResponse::StopPropagation;
            }
        }

        return EventCallbackResponse::None;
    }

    EventCallbackResponse Inputable::onEvent(EventChar *event) {
        if (this->focused) {
            this->text += event->value;
            if (this->callbackChange) {
                this->text = this->callbackChange(this->text);
            }
            return EventCallbackResponse::StopPropagation;
        }

        return EventCallbackResponse::None;
    }
}

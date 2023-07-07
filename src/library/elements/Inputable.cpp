//
// Created by noartem on 28.06.2022.
//

#include "Inputable.h"

#include <utility>
#include "../String.h"

namespace elementor::elements {
    std::shared_ptr<Inputable> inputable() {
        return std::make_shared<Inputable>();
    }

    std::shared_ptr<Inputable> Inputable::onChange(const std::function<std::u32string(std::u32string value)> &callback) {
        this->callbackChange = callback;
        return shared_from_this();
    }

    std::shared_ptr<Inputable> Inputable::onFocus(const std::function<void()> &callback) {
        this->callbackFocus = callback;
        return shared_from_this();
    }

    std::shared_ptr<Inputable> Inputable::onBlur(const std::function<void()> &callback) {
        this->callbackBlur = callback;
        return shared_from_this();
    }

    std::shared_ptr<Inputable> Inputable::setText(const std::u32string &newText) {
        this->text = newText;

        if (this->callbackChange) {
            this->callbackChange(this->text);
        }

        return shared_from_this();
    }

    std::shared_ptr<Inputable> Inputable::setText(const std::string& newText) {
        std::u32string newTextU32;
        fromUTF8(newText, newTextU32);
        return this->setText(newTextU32);
    }

    std::u32string Inputable::getText() {
        return this->text;
    }

    std::shared_ptr<Inputable> Inputable::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size Inputable::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Inputable::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) {
        this->rect = rect;
    }

    std::vector<RenderElement> Inputable::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        this->ctx = ctx;
        RenderElement childElement{this->getChild(), {0, 0}, rect.size};
        return {childElement};
    }

    EventCallbackResponse Inputable::onEvent(std::shared_ptr<EventHover> event) {
        this->hovered = event->hovered;
        return EventCallbackResponse::None;
    }

    EventCallbackResponse Inputable::onEvent(std::shared_ptr<EventMouseButton> event) {
        if (this->hovered) {
            if (event->action == KeyAction::Press && event->button == MouseButton::Left) {
                this->focus();
            }
        } else {
            this->blur();
        }

        return EventCallbackResponse::None;
    }

    EventCallbackResponse Inputable::onEvent(std::shared_ptr<EventKeyboard> event) {
        if (this->focused && (event->action == KeyAction::Press || event->action == KeyAction::Repeat)) {
            if (event->key == KeyboardKey::Escape || event->key == KeyboardKey::Enter) {
                this->blur();
                return EventCallbackResponse::StopPropagation;
            }

            if (event->key == KeyboardKey::C && event->mod == KeyMod::Control) {
                this->ctx->getClipboard()->set(toUTF8(this->text));
                return EventCallbackResponse::StopPropagation;
            }

            if (event->key == KeyboardKey::V && event->mod == KeyMod::Control) {
                std::string clipboardValueU8 = this->ctx->getClipboard()->get();
                std::u32string clipboardValueU32;
                fromUTF8(clipboardValueU8, clipboardValueU32);
                this->text += clipboardValueU32;
                if (this->callbackChange) {
                    this->text = this->callbackChange(this->text);
                }
                return EventCallbackResponse::StopPropagation;
            }

            if (event->key == KeyboardKey::Backspace && !this->text.empty()) {
                this->text.pop_back();
                if (this->callbackChange) {
                    this->text = this->callbackChange(this->text);
                }
                return EventCallbackResponse::StopPropagation;
            }
        }

        return EventCallbackResponse::None;
    }

    EventCallbackResponse Inputable::onEvent(std::shared_ptr<EventChar> event) {
        if (this->focused) {
            this->text += event->value;
            if (this->callbackChange) {
                this->text = this->callbackChange(this->text);
            }
            return EventCallbackResponse::StopPropagation;
        }

        return EventCallbackResponse::None;
    }

    void Inputable::blur() {
        if (!this->focused) {
            return;
        }

        this->focused = false;

        if (this->callbackBlur) {
            this->callbackBlur();
        }
    }

    void Inputable::focus() {
        if (this->focused) {
            return;
        }

        this->focused = true;

        if (this->callbackFocus) {
            this->callbackFocus();
        }
    }
}

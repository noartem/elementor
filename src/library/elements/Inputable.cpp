//
// Created by noartem on 28.06.2022.
//

#include "Inputable.h"

#include <iostream>
#include <iomanip>
#include <string_view>
#include <clocale>
#include <cuchar>
#include <climits>

std::string unicode_to_utf8(char32_t unicode) {
    std::string s;

    if (unicode>=0 and unicode <= 0x7f) { // 7F(16) = 127(10)
        s += static_cast<char>(unicode);
    } else if (unicode <= 0x7ff) { // 7FF(16) = 2047(10)
        unsigned char c1 = 192;
        unsigned char c2 = 128;

        for (int k=0; k<11; ++k) {
            if (k < 6)  c2 |= (unicode % 64) & (1 << k);
            else c1 |= (unicode >> 6) & (1 << (k - 6));
        }

        s += c1;
        s += c2;
    } else if (unicode <= 0xffff) { // FFFF(16) = 65535(10)
        unsigned char c1 = 224;
        unsigned char c2 = 128;
        unsigned char c3 = 128;

        for (int k = 0; k < 16; ++k) {
            if (k < 6)  c3 |= (unicode % 64) & (1 << k);
            else if (k < 12) c2 |= (unicode >> 6) & (1 << (k - 6));
            else c1 |= (unicode >> 12) & (1 << (k - 12));
        }

        s += c1;
        s += c2;
        s += c3;
    } else if (unicode <= 0x1fffff) { // 1FFFFF(16) = 2097151(10)
        unsigned char c1 = 240;
        unsigned char c2 = 128;
        unsigned char c3 = 128;
        unsigned char c4 = 128;

        for (int k = 0; k < 21; ++k) {
            if (k < 6)  c4 |= (unicode % 64) & (1 << k);
            else if (k < 12) c3 |= (unicode >> 6) & (1 << (k - 6));
            else if (k < 18) c2 |= (unicode >> 12) & (1 << (k - 12));
            else c1 |= (unicode >> 18) & (1 << (k - 18));
        }

        s += c1;
        s += c2;
        s += c3;
        s += c4;
    }

    return s;
}

void pop_back_utf8(std::string& utf8) {
    if(utf8.empty()){
        return;
    }

    auto cp = utf8.data() + utf8.size();

    while(--cp >= utf8.data() && ((*cp & 0b10000000) && !(*cp & 0b01000000))) {}

    if(cp >= utf8.data()) {
        utf8.resize(cp - utf8.data());
    }
}

namespace elementor::elements {
    Inputable *inputable() {
        return new Inputable();
    }

    Inputable *Inputable::onChange(std::function<std::string (std::string value)> callback) {
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
        if (this->focused && event->action == Action::Press) {
            if (event->key == KeyboardKey::Escape) {
                this->focused = false;
                if (this->callbackBlur) {
                    this->callbackBlur();
                }
                return EventCallbackResponse::StopPropagation;
            }

            if (event->key == KeyboardKey::Backspace && this->text.size() > 0) {
                pop_back_utf8(this->text);
                if (this->callbackChange) {
                    this->text = this->callbackChange(this->text);
                }
                std::cout << "EventKeyboard: " << this->text.size() << ", " << this->text << std::endl;
                return EventCallbackResponse::StopPropagation;
            }
        }

        return EventCallbackResponse::None;
    }

    EventCallbackResponse Inputable::onEvent(EventChar *event) {
        if (this->focused) {
            this->text += unicode_to_utf8(event->value);
            if (this->callbackChange) {
                this->text = this->callbackChange(this->text);
            }
            std::cout << "EventChar: " << this->text.size() << ", " << this->text << std::endl;
            return EventCallbackResponse::StopPropagation;
        }

        return EventCallbackResponse::None;
    }
}

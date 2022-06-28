//
// Created by noartem on 28.06.2022.
//

#include "Inputable.h"

#include <iostream>

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
            }

            bool isShift = event->mod == Mod::Shift;
            bool isCapslock = event->mod == Mod::CapsLock;
            bool isCapital = isCapslock || isShift;

            std::string newText = this->text;
            switch (event->key){
                case KeyboardKey::A:
                    newText += (isCapital ? "A" : "a");
                    break;
                case KeyboardKey::B:
                    newText += (isCapital ? "B" : "b");
                    break;
                case KeyboardKey::C:
                    newText += (isCapital ? "C" : "c");
                    break;
                case KeyboardKey::D:
                    newText += (isCapital ? "D" : "d");
                    break;
                case KeyboardKey::E:
                    newText += (isCapital ? "E" : "e");
                    break;
                case KeyboardKey::F:
                    newText += (isCapital ? "F" : "f");
                    break;
                case KeyboardKey::G:
                    newText += (isCapital ? "G" : "g");
                    break;
                case KeyboardKey::H:
                    newText += (isCapital ? "H" : "h");
                    break;
                case KeyboardKey::I:
                    newText += (isCapital ? "I" : "i");
                    break;
                case KeyboardKey::J:
                    newText += (isCapital ? "J" : "j");
                    break;
                case KeyboardKey::K:
                    newText += (isCapital ? "K" : "k");
                    break;
                case KeyboardKey::L:
                    newText += (isCapital ? "L" : "l");
                    break;
                case KeyboardKey::M:
                    newText += (isCapital ? "M" : "m");
                    break;
                case KeyboardKey::N:
                    newText += (isCapital ? "N" : "n");
                    break;
                case KeyboardKey::O:
                    newText += (isCapital ? "O" : "o");
                    break;
                case KeyboardKey::P:
                    newText += (isCapital ? "P" : "p");
                    break;
                case KeyboardKey::Q:
                    newText += (isCapital ? "Q" : "q");
                    break;
                case KeyboardKey::R:
                    newText += (isCapital ? "R" : "r");
                    break;
                case KeyboardKey::S:
                    newText += (isCapital ? "S" : "s");
                    break;
                case KeyboardKey::T:
                    newText += (isCapital ? "T" : "t");
                    break;
                case KeyboardKey::U:
                    newText += (isCapital ? "U" : "u");
                    break;
                case KeyboardKey::V:
                    newText += (isCapital ? "V" : "v");
                    break;
                case KeyboardKey::W:
                    newText += (isCapital ? "W" : "w");
                    break;
                case KeyboardKey::X:
                    newText += (isCapital ? "X" : "x");
                    break;
                case KeyboardKey::Y:
                    newText += (isCapital ? "Y" : "y");
                    break;
                case KeyboardKey::Z:
                    newText += (isCapital ? "Z" : "z");
                    break;
                case KeyboardKey::Number0:
                    newText += isShift ? ")" : "0";
                    break;
                case KeyboardKey::Number1World:
                case KeyboardKey::Number1:
                    newText += isShift ? "!" : "1";
                    break;
                case KeyboardKey::Number2World:
                case KeyboardKey::Number2:
                    newText += isShift ? "@" : "2";
                    break;
                case KeyboardKey::Number3:
                    newText += isShift ? "#" : "3";
                    break;
                case KeyboardKey::Number4:
                    newText += isShift ? "$" : "4";
                    break;
                case KeyboardKey::Number5:
                    newText += isShift ? "%" : "5";
                    break;
                case KeyboardKey::Number6:
                    newText += isShift ? "^" : "6";
                    break;
                case KeyboardKey::Number7:
                    newText += isShift ? "&" : "7";
                    break;
                case KeyboardKey::Number8:
                    newText += isShift ? "*" : "8";
                    break;
                case KeyboardKey::Number9:
                    newText += isShift ? "(" : "9";
                    break;
                case KeyboardKey::Space:
                    newText += " ";
                    break;
                case KeyboardKey::Apostraphe:
                    newText += isShift ? "\"" : "'";
                    break;
                case KeyboardKey::Comma:
                    newText += isShift ? "<" : ",";
                    break;
                case KeyboardKey::Period:
                    newText += isShift ? ">" : ".";
                    break;
                case KeyboardKey::Minus:
                    newText += isShift ? "_" : "-";
                    break;
                case KeyboardKey::Slash:
                    newText += isShift ? "?" : "/";
                    break;
                case KeyboardKey::Semicolon:
                    newText += isShift ? ":" : ";";
                    break;
                case KeyboardKey::Equal:
                    newText += isShift ? "+" : "=";
                    break;
                case KeyboardKey::LeftBracket:
                    newText += isShift ? "{" : "[";
                    break;
                case KeyboardKey::Backslash:
                    newText += isShift ? "|" : "\\";
                    break;
                case KeyboardKey::RightBracket:
                    newText += isShift ? "}" : "]";
                    break;
                case KeyboardKey::Backspace:
                    if (newText.size() > 0){
                        newText.pop_back();
                    }
                    break;
            }

            if (newText != this->text) {
                if (this->callbackChange) {
                    newText = this->callbackChange(newText);
                }
                this->text = newText;
                return EventCallbackResponse::StopPropagation;
            }
        }

        return EventCallbackResponse::None;
    }
}

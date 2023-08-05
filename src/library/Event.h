//
// Created by noartem on 09.05.2022.
//

#ifndef ELEMENTOR_EVENT_H
#define ELEMENTOR_EVENT_H

#include "Element.h"

#include <string>
#include <vector>

#define EVENT_MOUSE_BUTTON "mouse-button"
#define EVENT_MOUSE_MOVE "mouse-move"
#define EVENT_SCROLL "scroll"
#define EVENT_KEYBOARD "keyboard"
#define EVENT_CHAR "char"
#define EVENT_HOVER "hover"
#define EVENT_FOCUS "focus"

namespace elementor {
    class Event {
    public:
        virtual std::string getName() = 0;
    };

    std::vector<std::string> getElementEvents(const std::shared_ptr<Element>& element);

    enum class EventCallbackResponse {
        None,
        StopPropagation,
    };

    EventCallbackResponse callElementEventHandler(const std::shared_ptr<Element>& element, const std::shared_ptr<Event>& event);

    enum class MouseButton {
        Left,
        Right,
        Middle,
        Back,
        Forward,
    };

    enum class KeyAction {
        Release,
        Press,
        Repeat,
    };

    enum class KeyMod {
        None,
        Shift,
        Control,
        Alt,
        Super,
        CapsLock,
        NumLock,
    };

    enum class KeyboardKey {
        Unknow,
        Space,
        Apostraphe,
        Comma,
        Minus,
        Period,
        Slash,
        Number0,
        Number1World,
        Number1,
        Number2World,
        Number2,
        Number3,
        Number4,
        Number5,
        Number6,
        Number7,
        Number8,
        Number9,
        Semicolon,
        Equal,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        LeftBracket,
        Backslash,
        RightBracket,
        GraveAccent,
        Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,
        Right,
        Left,
        Down,
        Up,
        PageUp,
        PageDown,
        Home,
        End,
        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        F25,
        KP0,
        KP1,
        KP2,
        KP3,
        KP4,
        KP5,
        KP6,
        KP7,
        KP8,
        KP9,
        KPDecimal,
        KPDivide,
        KPMultiply,
        KPSubtract,
        KPAdd,
        KPEnter,
        KPEqual,
        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,
        Menu,
    };

    class EventMouseButton : public Event {
    public:
        EventMouseButton(MouseButton button, KeyAction action, KeyMod mod) {
            this->button = button;
            this->action = action;
            this->mod = mod;
        }

        MouseButton button;
        KeyAction action;
        KeyMod mod;

        std::string getName() override {
            return EVENT_MOUSE_BUTTON;
        };
    };

    class WithOnMouseButton {
    public:
        virtual EventCallbackResponse onEvent(std::shared_ptr<EventMouseButton> event) = 0;
    };

    class EventMouseMove : public Event {
    public:
        EventMouseMove(float x, float y) {
            this->x = x;
            this->y = y;
        }

        float x;
        float y;

        std::string getName() override {
            return EVENT_MOUSE_MOVE;
        };
    };

    class WithOnMouseMove {
    public:
        virtual EventCallbackResponse onEvent(std::shared_ptr<EventMouseMove> event) = 0;
    };

    class EventScroll : public Event {
    public:
        EventScroll(float xOffset, float yOffset) {
            this->xOffset = xOffset;
            this->yOffset = yOffset;
        }

        float xOffset;
        float yOffset;

        std::string getName() override {
            return EVENT_SCROLL;
        };
    };

    class WithOnScroll {
    public:
        virtual EventCallbackResponse onEvent(std::shared_ptr<EventScroll> event) = 0;
    };

    class EventKeyboard : public Event {
    public:
        EventKeyboard(KeyboardKey key, int scancode, KeyAction action, KeyMod mod) {
            this->key = key;
            this->scancode = scancode;
            this->action = action;
            this->mod = mod;
        }

        KeyboardKey key;
        int scancode;
        KeyAction action;
        KeyMod mod;

        std::string getName() override {
            return EVENT_KEYBOARD;
        };
    };

    class WithOnKeyboard {
    public:
        virtual EventCallbackResponse onEvent(std::shared_ptr<EventKeyboard> event) = 0;
    };

    class EventChar : public Event {
    public:
        explicit EventChar(char32_t value) {
            this->value = value;
        }

        char32_t value;

        std::string getName() override {
            return EVENT_CHAR;
        };
    };

    class WithOnChar {
    public:
        virtual EventCallbackResponse onEvent(std::shared_ptr<EventChar >event) = 0;
    };

    class EventHover : public Event {
    public:
        EventHover(bool hovered) {
            this->hovered = hovered;
        }

        bool hovered;

        std::string getName() override {
            return EVENT_HOVER;
        };
    };

    class WithOnHover {
    public:
        virtual EventCallbackResponse onEvent(std::shared_ptr<EventHover> event) = 0;
    };

    class EventFocus : public Event {
    public:
        EventFocus(std::shared_ptr<Element> element) {
            this->element = element;
        }

        std::shared_ptr<Element> element;

        std::string getName() override {
            return EVENT_FOCUS;
        };
    };

    class WithOnFocus {
    public:
        virtual EventCallbackResponse onEvent(std::shared_ptr<EventFocus> event) = 0;
    };
}

#endif //ELEMENTOR_EVENT_H

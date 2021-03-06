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

namespace elementor {
    class Event {
    public:
        virtual std::string getName() = 0;
    };

    std::vector<std::string> getElementEvents(Element *element);

    enum class EventCallbackResponse {
        None,
        StopPropagation,
    };

    EventCallbackResponse callElementEventHandler(Element *element, Event *event);

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

    class EventMouseButton: public Event {
    public:
        MouseButton button;
        KeyAction action;
        KeyMod mod;

        std::string getName() { return EVENT_MOUSE_BUTTON; };
    };

    class WithOnMouseButton {
    public:
        virtual EventCallbackResponse onEvent(EventMouseButton *event) = 0;
    };

    class EventMouseMove: public Event {
    public:
        float x;
        float y;

        std::string getName() { return EVENT_MOUSE_MOVE; };
    };

    class WithOnMouseMove {
    public:
        virtual EventCallbackResponse onEvent(EventMouseMove *event) = 0;
    };

    class EventScroll: public Event {
    public:
        float xOffset;
        float yOffset;

        std::string getName() { return EVENT_SCROLL; };
    };

    class WithOnScroll {
    public:
        virtual EventCallbackResponse onEvent(EventScroll *event) = 0;
    };

    class EventKeyboard: public Event {
    public:
        KeyboardKey key;
        int scancode;
        KeyAction action;
        KeyMod mod;

        std::string getName() { return EVENT_KEYBOARD; };
    };

    class WithOnKeyboard {
    public:
        virtual EventCallbackResponse onEvent(EventKeyboard *event) = 0;
    };

    class EventChar: public Event {
    public:
        char32_t value;

        std::string getName() { return EVENT_CHAR; };
    };

    class WithOnChar {
    public:
        virtual EventCallbackResponse onEvent(EventChar *event) = 0;
    };
}

#endif //ELEMENTOR_EVENT_H

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

    enum class Mod {
        None,
        Shift,
        Control,
        Alt,
        Super,
        CapsLock,
        NumLock,
    };

    enum class KeyboardKey {
        // TODO: Map number to enum in Platform
        Unknow = -1,
        Space = 32,
        Apostraphe = 39,
        Comma = 44,
        Minus = 45,
        Period = 46,
        Slash = 47,
        Number0 = 48,
        Number1World = 161,
        Number1 = 49,
        Number2World = 162,
        Number2 = 50,
        Number3 = 51,
        Number4 = 52,
        Number5 = 53,
        Number6 = 54,
        Number7 = 55,
        Number8 = 56,
        Number9 = 57,
        Semicolon = 59,
        Equal = 61,
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        LeftBracket = 91,
        Backslash = 92,
        RightBracket = 93,
        GraveAccent = 96,
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,
        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDecimal = 330,
        KPDivide = 331,
        KPMultiply = 332,
        KPSubtract = 333,
        KPAdd = 334,
        KPEnter = 335,
        KPEqual = 336,
        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftSuper = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightSuper = 347,
        Menu = 348,
    };

    class EventMouseButton: public Event {
    public:
        MouseButton button;
        KeyAction action;
        Mod mod;

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
        Mod mod;

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

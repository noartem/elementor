//
// Created by noartem on 09.05.2022.
//

#ifndef ELEMENTOR_EVENT_H
#define ELEMENTOR_EVENT_H

#include "Element.h"

#include <string>
#include <vector>

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
        Forward
    };

    enum class MouseAction {
        Release,
        Press,
        Repeat,
    };

    enum class MouseMod {
        Shift,
        Control,
        Alt,
        Super,
        CapsLock,
        NumLock,
    };

    class EventMouseButton: public Event {
    public:
        MouseButton button;
        MouseAction action;
        MouseMod mod;

        std::string getName();
    };

    class WithOnMouseButton {
    public:
        virtual EventCallbackResponse onEvent(EventMouseButton *event) = 0;
    };

    class EventMouseMove: public Event {
    public:
        float x;
        float y;

        std::string getName();
    };

    class WithOnMouseMove {
    public:
        virtual EventCallbackResponse onEvent(EventMouseMove *event) = 0;
    };
}

#endif //ELEMENTOR_EVENT_H

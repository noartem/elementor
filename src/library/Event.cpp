//
// Created by noartem on 09.05.2022.
//

#include "Event.h"

namespace elementor {
    std::vector<std::string> getElementEvents(Element *element) {
        std::vector<std::string> events;

        if (dynamic_cast<WithOnMouseButton *>(element) != nullptr) {
            events.emplace_back(EVENT_MOUSE_BUTTON);
        }

        if (dynamic_cast<WithOnMouseMove *>(element) != nullptr) {
            events.emplace_back(EVENT_MOUSE_MOVE);
        }

        if (dynamic_cast<WithOnScroll *>(element) != nullptr) {
            events.emplace_back(EVENT_SCROLL);
        }

        if (dynamic_cast<WithOnKeyboard *>(element) != nullptr) {
            events.emplace_back(EVENT_KEYBOARD);
        }

        if (dynamic_cast<WithOnChar *>(element) != nullptr) {
            events.emplace_back(EVENT_CHAR);
        }

        return events;
    }

    EventCallbackResponse callElementEventHandler(Element *element, Event *event) {
        std::string eventName = event->getName();
        if (eventName == EVENT_MOUSE_BUTTON) {
            return dynamic_cast<WithOnMouseButton *>(element)->onEvent(dynamic_cast<EventMouseButton *>(event));
        } else if (eventName == EVENT_MOUSE_MOVE) {
            return dynamic_cast<WithOnMouseMove *>(element)->onEvent(dynamic_cast<EventMouseMove *>(event));
        } else if (eventName == EVENT_SCROLL) {
            return dynamic_cast<WithOnScroll *>(element)->onEvent(dynamic_cast<EventScroll *>(event));
        } else if (eventName == EVENT_KEYBOARD) {
            return dynamic_cast<WithOnKeyboard *>(element)->onEvent(dynamic_cast<EventKeyboard *>(event));
        } else if (eventName == EVENT_CHAR) {
            return dynamic_cast<WithOnChar *>(element)->onEvent(dynamic_cast<EventChar *>(event));
        }

        return EventCallbackResponse::None;
    }
}

//
// Created by noartem on 09.05.2022.
//

#include "Event.h"

namespace elementor {
    std::vector<std::string> getElementEvents(Element *element) {
        std::vector<std::string> events;

        if (dynamic_cast<WithOnMouseButton *>(element) != NULL) {
            events.push_back(EVENT_MOUSE_BUTTON);
        }

        if (dynamic_cast<WithOnMouseMove *>(element) != NULL) {
            events.push_back(EVENT_MOUSE_MOVE);
        }

        if (dynamic_cast<WithOnScroll *>(element) != NULL) {
            events.push_back(EVENT_SCROLL);
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
        }

        return EventCallbackResponse::None;
    }
}

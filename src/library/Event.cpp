//
// Created by noartem on 09.05.2022.
//

#include "Event.h"

#define EVENT_MOUSE_BUTTON "mouse-button"
#define EVENT_MOUSE_MOVE "mouse-move"

namespace elementor {
    std::string EventMouseButton::getName() {
        return EVENT_MOUSE_BUTTON;
    }

    std::string EventMouseMove::getName() {
        return EVENT_MOUSE_MOVE;
    }

    std::vector<std::string> getElementEvents(Element *element) {
        std::vector<std::string> events;

        if (dynamic_cast<WithOnMouseButton *>(element) != NULL) {
            events.push_back(EVENT_MOUSE_BUTTON);
        }

        if (dynamic_cast<WithOnMouseMove *>(element) != NULL) {
            events.push_back(EVENT_MOUSE_MOVE);
        }

        return events;
    }

    EventCallbackResponse callElementEventHandler(Element *element, Event *event) {
        std::string eventName = event->getName();
        if (eventName == EVENT_MOUSE_BUTTON) {
            return dynamic_cast<WithOnMouseButton *>(element)->onEvent(dynamic_cast<EventMouseButton *>(event));
        } else if (eventName == EVENT_MOUSE_MOVE) {
            return dynamic_cast<WithOnMouseMove *>(element)->onEvent(dynamic_cast<EventMouseMove *>(event));
        }

        return EventCallbackResponse::None;
    }
}

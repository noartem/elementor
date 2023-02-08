//
// Created by noartem on 09.05.2022.
//

#include "Event.h"

namespace elementor {
    std::vector<std::string> getElementEvents(const std::shared_ptr<Element>& element) {
        std::vector<std::string> events;

        if (dynamic_cast<WithOnMouseButton *>(element.get()) != nullptr) {
            events.emplace_back(EVENT_MOUSE_BUTTON);
        }

        if (dynamic_cast<WithOnMouseMove *>(element.get()) != nullptr) {
            events.emplace_back(EVENT_MOUSE_MOVE);
        }

        if (dynamic_cast<WithOnMouseWillMove *>(element.get()) != nullptr) {
            events.emplace_back(EVENT_MOUSE_WILL_MOVE);
        }

        if (dynamic_cast<WithOnScroll *>(element.get()) != nullptr) {
            events.emplace_back(EVENT_SCROLL);
        }

        if (dynamic_cast<WithOnKeyboard *>(element.get()) != nullptr) {
            events.emplace_back(EVENT_KEYBOARD);
        }

        if (dynamic_cast<WithOnChar *>(element.get()) != nullptr) {
            events.emplace_back(EVENT_CHAR);
        }

        return events;
    }

    EventCallbackResponse callElementEventHandler(const std::shared_ptr<Element>& element, const std::shared_ptr<Event>& event) {
        std::string eventName = event->getName();
        if (eventName == EVENT_MOUSE_BUTTON) {
            return dynamic_cast<WithOnMouseButton *>(element.get())->onEvent(std::dynamic_pointer_cast<EventMouseButton>(event));
        } else if (eventName == EVENT_MOUSE_MOVE) {
            return dynamic_cast<WithOnMouseMove *>(element.get())->onEvent(std::dynamic_pointer_cast<EventMouseMove>(event));
        } else if (eventName == EVENT_MOUSE_WILL_MOVE) {
            return dynamic_cast<WithOnMouseWillMove *>(element.get())->onEvent(std::dynamic_pointer_cast<EventMouseWillMove>(event));
        } else if (eventName == EVENT_SCROLL) {
            return dynamic_cast<WithOnScroll *>(element.get())->onEvent(std::dynamic_pointer_cast<EventScroll>(event));
        } else if (eventName == EVENT_KEYBOARD) {
            return dynamic_cast<WithOnKeyboard *>(element.get())->onEvent(std::dynamic_pointer_cast<EventKeyboard>(event));
        } else if (eventName == EVENT_CHAR) {
            return dynamic_cast<WithOnChar *>(element.get())->onEvent(std::dynamic_pointer_cast<EventChar>(event));
        }

        return EventCallbackResponse::None;
    }
}

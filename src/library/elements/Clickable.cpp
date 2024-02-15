//
// Created by noartem on 21.05.2022.
//

#include "Clickable.h"

namespace elementor::elements {
	Size Clickable::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		return child->getSize(boundaries);
	}

	std::vector <ElementWithRect> Clickable::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Rect childRect = {
			.size = rect.size,
			.position = { .x = 0, .y = 0 }
		};

		ElementWithRect childElement(child, childRect);
		return { childElement };
	}

	std::vector <std::shared_ptr<EventHandler>> Clickable::getEventsHandlers() {
		return {
			HoverEvent::Handle([this](const auto& event) {
				hovered = event->hovered;
				return EventCallbackResponse::None;
			}),
			MouseButtonEvent::Handle([this](const auto& event) {
				if (!hovered || event->action != KeyAction::Release) {
					return EventCallbackResponse::None;
				}

				if (callbackButton.has_value()) {
					auto callback = callbackButton.value();
					EventCallbackResponse callbackResponse = callback(event->button, event->mod);
					if (callbackResponse != EventCallbackResponse::None) {
						return callbackResponse;
					}
				}

				if (event->button == MouseButton::Left && callbackClick.has_value()) {
					auto callback = callbackClick.value();
					EventCallbackResponse callbackResponse = callback(event->mod);
					if (callbackResponse != EventCallbackResponse::None) {
						return callbackResponse;
					}
				}

				return EventCallbackResponse::None;
			})
		};
	}
}

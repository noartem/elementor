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

	std::vector<ElementWithRect> Clickable::getChildren(const ElementRect& rect) {
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

	EventCallbackResponse Clickable::onEvent(const std::shared_ptr<Event>& event) {
		auto hoverEvent = std::dynamic_pointer_cast<HoverEvent>(event);
		if (hoverEvent) {
			hovered = hoverEvent->hovered;
			return EventCallbackResponse::None;
		}

		auto mouseButtonEvent = std::dynamic_pointer_cast<MouseButtonEvent>(event);
		if (mouseButtonEvent) {
			if (!hovered || mouseButtonEvent->action != KeyAction::Press) {
				return EventCallbackResponse::None;
			}

			if (callbackButton.has_value()) {
				auto callback = callbackButton.value();
				EventCallbackResponse callbackResponse = callback(mouseButtonEvent->button, mouseButtonEvent->mod);
				if (callbackResponse != EventCallbackResponse::None) {
					return callbackResponse;
				}
			}

			if (mouseButtonEvent->button == MouseButton::Left && callbackClick.has_value()) {
				auto callback = callbackClick.value();
				EventCallbackResponse callbackResponse = callback(mouseButtonEvent->mod);
				if (callbackResponse != EventCallbackResponse::None) {
					return callbackResponse;
				}
			}

			return EventCallbackResponse::None;
		}

		return EventCallbackResponse::None;

	}
}

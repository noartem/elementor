//
// Created by noartem on 18.05.2022.
//

#include "Hoverable.h"

namespace elementor::elements {
	Size Hoverable::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		return child->getSize(boundaries);
	}

	std::vector<ElementWithRect> Hoverable::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Rect childRect = {
			.size = rect.size,
			.position = { .x = 0, .y = 0 },
		};

		ElementWithRect childElement(child, childRect);
		return { childElement };
	}

	std::vector<std::shared_ptr<EventHandler>> Hoverable::getEventsHandlers() {
		return {
			HoverEvent::Handle([this](const auto& event) {
				if (callbackLeave && hovered && !event->hovered) {
					hovered = false;
					return callbackLeave();
				}

				if (callbackEnter && !hovered && event->hovered) {
					hovered = true;
					return callbackEnter();
				}

				hovered = event->hovered;
				return EventCallbackResponse::None;
			})
		};
	}
}

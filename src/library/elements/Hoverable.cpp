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

	EventCallbackResponse Hoverable::onEvent(const std::shared_ptr<Event>& event) {
		auto hoverEvent = std::dynamic_pointer_cast<HoverEvent>(event);
		if (hoverEvent) {
			if (callbackLeave && hovered && !hoverEvent->hovered) {
				hovered = false;
				return callbackLeave();
			}

			if (callbackEnter && !hovered && hoverEvent->hovered) {
				hovered = true;
				return callbackEnter();
			}

			hovered = hoverEvent->hovered;
			return EventCallbackResponse::None;
		}

		return EventCallbackResponse::None;
	}
}

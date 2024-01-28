//
// Created by noartem on 18.05.2022.
//

#include "Focusable.h"

namespace elementor::elements {
	Size Focusable::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		return child->getSize(boundaries);
	}

	std::vector<ElementWithRect> Focusable::getChildren(const ElementRect& rect) {
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

	EventCallbackResponse Focusable::onEvent(const std::shared_ptr<Event>& event) {
		auto focusEvent = std::dynamic_pointer_cast<FocusEvent>(event);
		if (focusEvent) {
			if (callbackFocusChange.has_value()) {
				callbackFocusChange.value()(focusEvent->focused);
				return EventCallbackResponse::StopPropagation;
			}

			return EventCallbackResponse::None;
		}

		return EventCallbackResponse::None;
	}
}

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

	std::vector<std::shared_ptr<EventHandler>> Focusable::getEventsHandlers() {
		return {
			FocusEvent::Handle([this](const auto& event) {
				focused = event->focused;

				pendingBlur = false;
				pendingFocus = false;

				if (callbackFocusChange.has_value()) {
					callbackFocusChange.value()(event->focused);
				}

				return EventCallbackResponse::None;
			})
		};
	}
}

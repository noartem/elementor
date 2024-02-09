//
// Created by noartem on 01.02.2024.
//

#include "Outline.h"

namespace elementor::components {
	Size Outline::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		return getChild()->getSize(boundaries);
	}

	std::vector<ElementWithRect> Outline::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		std::vector<ElementWithRect> children;

		if (focused) {
			auto pixelScale = ctx->getPixelScale();
			auto offsetScaled = offset * pixelScale;

			Rect borderRect = {
				.size = {
					.width = rect.size.width + offsetScaled * 2,
					.height = rect.size.height + offsetScaled * 2,
				},
				.position = {
					.x = -1 * offsetScaled,
					.y = -1 * offsetScaled
				},
			};
			ElementWithRect borderElementWithRect(borderAsElement, borderRect);
			children.push_back(borderElementWithRect);
		}

		Rect childRect = {
			.size = rect.size,
			.position = { .x = 0.0f, .y = 0.0f },
		};
		ElementWithRect childElementWithRect(child, childRect);
		children.push_back(childElementWithRect);

		return children;
	}

	void Outline::setFocused(bool newFocused) {
		focused = newFocused;
	}

	std::vector<std::shared_ptr<EventHandler>> Outline::getEventsHandlers() {
		return {
			FocusInEvent::Handle([this](const auto& event) {
				setFocused(true);
				return EventCallbackResponse::None;
			}),
			FocusOutEvent::Handle([this](const auto& event) {
				setFocused(false);
				return EventCallbackResponse::None;
			})
		};
	}
}

//
// Created by noartem on 22.05.2022.
//

#include "Scrollable.h"

namespace elementor::elements {
	Size Scrollable::getChildSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		Boundaries childBoundaries = {
			.min = boundaries.min,
			.max = {
				.width = isHorizontalScroll() ? Infinity : boundaries.max.width,
				.height = isVerticalScroll() ? Infinity : boundaries.max.height,
			}
		};

		return child->getSize(childBoundaries);
	}

	Size Scrollable::getSize(const Boundaries& boundaries) {
		return fitSizeInBoundaries(getChildSize(boundaries), boundaries);
	}

	std::vector<ElementWithRect> Scrollable::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Size childSize = getChildSize({
			.min = ZeroSize,
			.max = {
				.width = rect.size.width,
				.height = rect.size.height,
			}
		});

		lastChildSize = childSize;
		lastSize = rect.size;

		setScrollLeft(scrollLeft);
		setScrollTop(scrollTop);

		Rect childRect = {
			.size = childSize,
			.position = {
				.x = -1 * scrollLeft,
				.y = -1 * scrollTop
			},
		};

		ElementWithRect childElement(child, childRect);
		return { childElement };
	}

	std::vector<std::shared_ptr<EventHandler>> Scrollable::getEventsHandlers() {
		return {
			HoverEvent::Handle([this](const auto& event) {
				hovered = event->hovered;
				return EventCallbackResponse::None;
			}),
			ScrollEvent::Handle([this](const auto& event) {
				if (!this->hovered) {
					return EventCallbackResponse::None;
				}

				setScrollLeft(scrollLeft - event->xOffset * scrollAcceleration);
				setScrollTop(scrollTop - event->yOffset * scrollAcceleration);

				return EventCallbackResponse::StopPropagation;
			})
		};
	}
}

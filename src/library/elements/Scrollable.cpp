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
		lastChildSize = getChildSize(boundaries);
		return fitSizeInBoundaries(lastChildSize, boundaries);
	}

	void Scrollable::paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		if (rect.size == lastSize) {
			return;
		}

		if (isHorizontalScroll() && rect.size.width + scrollLeft > lastChildSize.width) {
			scrollLeft = std::min(
				std::max(lastChildSize.width - rect.size.width, 0.0f),
				getMaxScrollLeft()
			);
		}

		if (isVerticalScroll() && rect.size.height + scrollTop > lastChildSize.height) {
			scrollTop = std::min(
				std::max(lastChildSize.height - rect.size.height, 0.0f),
				getMaxScrollTop()
			);
		}

		lastSize = rect.size;
	}

	std::vector<ElementWithRect> Scrollable::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Rect childRect = {
			.size = getChildSize({
				.min = ZeroSize,
				.max = {
					.width = rect.size.width,
					.height = rect.size.height,
				}
			}),
			.position = {
				.x = -1 * scrollLeft,
				.y = -1 * scrollTop
			},
		};
		lastChildSize = childRect.size;

		ElementWithRect childElement(child, childRect);

		return { childElement };
	}

	EventCallbackResponse Scrollable::onScrollEvent(const std::shared_ptr<ScrollEvent>& event) {
		if (!this->hovered) {
			return EventCallbackResponse::None;
		}

		setScrollLeft(scrollLeft - event->xOffset * scrollAcceleration);
		setScrollTop(scrollTop - event->yOffset * scrollAcceleration);

		return EventCallbackResponse::StopPropagation;
	}

	EventCallbackResponse Scrollable::onEvent(const std::shared_ptr<Event>& event) {
		auto hoverEvent = std::dynamic_pointer_cast<HoverEvent>(event);
		if (hoverEvent) {
			hovered = hoverEvent->hovered;
			return EventCallbackResponse::None;
		}

		auto scrollEvent = std::dynamic_pointer_cast<ScrollEvent>(event);
		if (scrollEvent) {
			return onScrollEvent(scrollEvent);
		}

		return EventCallbackResponse::None;
	}
}

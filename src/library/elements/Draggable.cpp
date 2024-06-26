//
// Created by noartem on 21.05.2022.
//

#include "Draggable.h"

namespace elementor::elements {
	Size Draggable::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		return child->getSize(boundaries);
	}

	void Draggable::paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		lastRect = rect;
	}

	std::vector<ElementWithRect> Draggable::getChildren(const ElementRect& rect) {
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

	std::vector<std::shared_ptr<EventHandler>> Draggable::getGlobalEventsHandlers() {
		return {
			MouseMoveEvent::Handle([this](const auto& event) {
				onApplicationMouseMoveEvent(event);
				return EventCallbackResponse::None;
			}),
			MouseButtonEvent::Handle([this](const auto& event) {
				onApplicationMouseButtonEvent(event);
				return EventCallbackResponse::None;
			}),
		};
	}

	void Draggable::onApplicationMouseMoveEvent(const std::shared_ptr<MouseMoveEvent>& event) {
		if (!dragging) {
			return;
		}

		previousCursorAbsolutePosition = cursorAbsolutePosition;
		cursorAbsolutePosition = { .x = event->x, .y = event->y };

		if (previousCursorAbsolutePosition == InvalidPosition) {
			return;
		}

		cursorPosition = lastRect.absolutePositionToContained(cursorAbsolutePosition);

		if (callbackMove.has_value()) {
			Position cursorPositionDiff = {
				.x = cursorAbsolutePosition.x - previousCursorAbsolutePosition.x,
				.y = cursorAbsolutePosition.y - previousCursorAbsolutePosition.y,
			};
			callbackMove.value()(
				cursorPosition,
				cursorAbsolutePosition,
				cursorPositionDiff
			);
		}
	}

	void Draggable::onApplicationMouseButtonEvent(const std::shared_ptr<MouseButtonEvent>& event) {
		if (!dragging || event->button != MouseButton::Left || event->action != KeyAction::Release) {
			return;
		}

		if (callbackEnd.has_value()) {
			callbackEnd.value()(cursorPosition, cursorAbsolutePosition);
		}

		setDragging(false);
	}

	std::vector<std::shared_ptr<EventHandler>> Draggable::getEventsHandlers() {
		return {
			HoverEvent::Handle([this](const auto& event) {
				hovered = event->hovered;
				return EventCallbackResponse::None;
			}),
			MouseButtonEvent::Handle([this](const auto& event) {
				if (dragging || !hovered || event->button != MouseButton::Left || event->action != KeyAction::Press) {
					return EventCallbackResponse::None;
				}

				if (callbackStart.has_value()) {
					bool startAllowed = callbackStart.value()(cursorPosition, cursorAbsolutePosition);
					if (!startAllowed) {
						return EventCallbackResponse::None;
					}
				}

				setDragging(true);

				return EventCallbackResponse::StopPropagation;
			}),
		};
	}
}

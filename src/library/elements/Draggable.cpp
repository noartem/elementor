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

	void Draggable::onApplicationMouseMoveEvent(const std::shared_ptr<MouseMoveEvent>& event) {
		if (!dragging) {
			return;
		}

		previousCursorAbsolutePosition = cursorAbsolutePosition;
		cursorAbsolutePosition = { event->x, event->y };
		cursorPosition = lastRect.absolutePositionToContained(cursorAbsolutePosition);

		if (callbackMove.has_value()) {
			Position cursorPositionDiff = {
				.x = cursorAbsolutePosition.x - previousCursorAbsolutePosition.x,
				.y = cursorAbsolutePosition.y - previousCursorAbsolutePosition.y,
			};
			callbackMove.value()(
				this->cursorPosition,
				this->cursorAbsolutePosition,
				cursorPositionDiff
			);
		}
	}

	void Draggable::onApplicationMouseButtonEvent(const std::shared_ptr<MouseButtonEvent>& event) {
		if (!dragging || event->button != MouseButton::Left || event->action != KeyAction::Release) {
			return;
		}

		if (callbackEnd.has_value()) {
			callbackEnd.value()(this->cursorPosition, this->cursorAbsolutePosition);
		}

		dragging = false;

		ctx->removeEventListener("mouse-move", mouseMoveListenerId);
		ctx->removeEventListener("mouse-button", mouseButtonListenerId);
	}

	void Draggable::onMouseButtonEvent(const std::shared_ptr<MouseButtonEvent>& event) {
		if (dragging || !hovered || event->button != MouseButton::Left || event->action != KeyAction::Press) {
			return;
		}

		if (callbackStart.has_value()) {
			bool startAllowed = callbackStart.value()(cursorPosition, cursorAbsolutePosition);
			if (!startAllowed) {
				return;
			}
		}

		dragging = true;

		mouseMoveListenerId = ctx->addEventListener("mouse-move", [this](const std::shared_ptr<Event>& event) {
			auto mouseMoveEvent = std::dynamic_pointer_cast<MouseMoveEvent>(event);
			if (mouseMoveEvent) {
				onApplicationMouseMoveEvent(mouseMoveEvent);
			}
		});

		mouseButtonListenerId = ctx->addEventListener("mouse-button", [this](const std::shared_ptr<Event>& event) {
			auto mouseButtonEvent = std::dynamic_pointer_cast<MouseButtonEvent>(event);
			if (mouseButtonEvent) {
				onApplicationMouseButtonEvent(mouseButtonEvent);
			}
		});
	}

	EventCallbackResponse Draggable::onEvent(const std::shared_ptr<Event>& event) {
		auto hoverEvent = std::dynamic_pointer_cast<HoverEvent>(event);
		if (hoverEvent) {
			hovered = hoverEvent->hovered;
			return EventCallbackResponse::None;
		}

		auto mouseButtonEvent = std::dynamic_pointer_cast<MouseButtonEvent>(event);
		if (mouseButtonEvent) {
			onMouseButtonEvent(mouseButtonEvent);
			return EventCallbackResponse::None;
		}

		return EventCallbackResponse::None;
	}
}

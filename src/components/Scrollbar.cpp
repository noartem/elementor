//
// Created by noartem on 26.05.2022.
//

#include "Scrollbar.h"

namespace elementor::elements {
	void Scrollbar::setThumb(const std::shared_ptr<Element>& newThumb) {
		markChanged();

		if (newThumb == nullptr) {
			thumbX = nullptr;
			thumbY = nullptr;
			return;
		}

		thumbX = Draggable::New(ctx, {
			.onMove = [this](Position p, Position ap, Position diff) {
				auto scrollDiff = diff.x * child->getScrollSize().width / child->getSize().width;
				child->setScrollLeft(child->getScrollLeft() + scrollDiff);
			},
			.child = Padding::New(ctx, {
				.x = spacing,
				.bottom = spacing,
				.child = newThumb
			})
		});

		thumbY = Draggable::New(ctx, {
			.onMove = [this](Position p, Position ap, Position diff) {
				auto scrollDiff = diff.y * child->getScrollSize().height / child->getSize().height;
				child->setScrollTop(child->getScrollTop() + scrollDiff);
			},
			.child = Padding::New(ctx, {
				.y = spacing,
				.right = spacing,
				.child = newThumb
			})
		});
	}

	Size Scrollbar::getSize(const Boundaries& boundaries) {
		if (child == nullptr) {
			return boundaries.max;
		}

		return child->getSize(boundaries);
	}

	std::vector<ElementWithRect> Scrollbar::getChildren(const ElementRect& rect) {
		lastRect = rect;

		if (child == nullptr) {
			return {};
		}

		std::vector<ElementWithRect> children;

		Rect childRect = { .size = rect.size, .position = ZeroPosition };
		auto childAsElement = std::dynamic_pointer_cast<Element>(child);
		ElementWithRect childElementRect(childAsElement, childRect);
		children.push_back(childElementRect);

		bool withThumbX = thumbX && child->getMaxScrollLeft() > 0;
		bool withThumbY = thumbY && child->getMaxScrollTop() > 0;

		auto pixelScale = ctx->getPixelScale();
		auto thicknessScaled = thickness * pixelScale;

		if (withThumbX) {
			Rect thumbXRect = {
				.size = {
					.width = (child->getSize().width / child->getScrollSize().width)
						* (rect.size.width - (withThumbY ? thicknessScaled : 0)),
					.height = thicknessScaled
				},
				.position = {
					.x = (child->getScrollLeft() / child->getScrollSize().width)
						* (rect.size.width - (withThumbY ? thicknessScaled : 0)),
					.y = rect.size.height - thicknessScaled
				}
			};

			ElementWithRect thumbXElementRect(thumbX, thumbXRect);
			children.push_back(thumbXElementRect);
		}

		if (withThumbY) {
			Rect thumbYRect = {
				.size = {
					.width = thicknessScaled,
					.height = (child->getSize().height / child->getScrollSize().height)
						* (rect.size.height - (withThumbX ? thicknessScaled : 0))
				},
				.position = {
					.x = rect.size.width - thicknessScaled,
					.y = (child->getScrollTop() / child->getScrollSize().height)
						* (rect.size.height - (withThumbX ? thicknessScaled : 0))
				}
			};

			ElementWithRect thumbYElementRect(thumbY, thumbYRect);
			children.push_back(thumbYElementRect);
		}

		return children;
	}

	std::vector<std::shared_ptr<EventHandler>> Scrollbar::getEventsHandlers() {
		return {
			MouseButtonEvent::Handle([this](const auto& event) {
				if (event->button != MouseButton::Left || event->action != KeyAction::Press) {
					return EventCallbackResponse::None;
				}

				auto cursorAbsolutePosition = this->ctx->getCursor()->getPosition();
				auto cursorPosition = lastRect.absolutePositionToContained(cursorAbsolutePosition);

				auto pixelScale = ctx->getPixelScale();
				auto thicknessScaled = thickness * pixelScale;

				if (child->getMaxScrollLeft() > 0 && cursorPosition.y > (lastRect.size.height - thicknessScaled * 2)) {
					child->setScrollLeft(
						(cursorPosition.x / lastRect.size.width) * child->getScrollSize().width
					);

					auto thumbXDraggable = std::dynamic_pointer_cast<Draggable>(thumbX);
					thumbXDraggable->setDragging(true);

					return EventCallbackResponse::StopPropagation;
				}

				if (child->getMaxScrollTop() > 0 && cursorPosition.x > (lastRect.size.width - thicknessScaled * 2)) {
					child->setScrollTop(
						(cursorPosition.y / lastRect.size.height) * child->getScrollSize().height
					);

					auto thumbYDraggable = std::dynamic_pointer_cast<Draggable>(thumbY);
					thumbYDraggable->setDragging(true);

					return EventCallbackResponse::StopPropagation;
				}

				return EventCallbackResponse::None;
			})
		};
	}
}

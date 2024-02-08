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
			.child = newThumb,
		});

		thumbY = Draggable::New(ctx, {
			.onMove = [this](Position p, Position ap, Position diff) {
				E_PRINT(diff.y);
				auto scrollDiff = diff.y * child->getScrollSize().height / child->getSize().height;
				child->setScrollTop(child->getScrollTop() + scrollDiff);
			},
			.child = newThumb,
		});
	}

	Size Scrollbar::getSize(const Boundaries& boundaries) {
		if (child == nullptr) {
			return boundaries.max;
		}

		return child->getSize(boundaries);
	}

	std::vector<ElementWithRect> Scrollbar::getChildren(const ElementRect& rect) {
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

		if (child->getMaxScrollLeft() > 0) {
			Rect thumbXRect = {
				.size = {
					.width = (child->getSize().width / child->getScrollSize().width)
						* (rect.size.width - (withThumbY ? thickness : 0)) - spacing * 2,
					.height = thickness - spacing
				},
				.position = {
					.x = (child->getScrollLeft() / child->getScrollSize().width)
						* (rect.size.width - (withThumbY ? thickness : 0)) + spacing,
					.y = rect.size.height - thickness - spacing
				}
			};

			ElementWithRect trackXElementRect(thumbX, thumbXRect);
			children.push_back(trackXElementRect);
		}

		if (child->getMaxScrollTop() > 0) {
			Rect thumbYRect = {
				.size = {
					.width = thickness - spacing,
					.height = (child->getSize().height / child->getScrollSize().height)
						* (rect.size.height - (withThumbX ? thickness : 0)) - spacing * 2
				},
				.position = {
					.x = rect.size.width - thickness - spacing,
					.y = (child->getScrollTop() / child->getScrollSize().height)
						* (rect.size.height - (withThumbX ? thickness : 0)) + spacing
				}
			};

			ElementWithRect trackYElementRect(thumbY, thumbYRect);
			children.push_back(trackYElementRect);
		}

		return children;
	}
}

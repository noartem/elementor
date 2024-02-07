//
// Created by noartem on 26.05.2022.
//

#include "Scrollbar.h"

#include "Clickable.h"
#include "Draggable.h"

namespace elementor::elements {
	void Scrollbar::setTrackX(const std::shared_ptr<Element>& newTrackX) {
		if (newTrackX == nullptr) {
			trackX = nullptr;
			return;
		}

		trackX = Clickable::New(ctx, {
//			->onClick([this] (const std::shared_ptr<MouseButtonEvent>& event, Position position) {
//				float positionX = (position.x / this->child->getWidth()) * this->child->getScrollWidth();
//				this->child->setScrollLeft(positionX - (this->child->getWidth() / 2));
//				return EventCallbackResponse::StopPropagation;
//			})
			.child = newTrackX,
		});
	}

	void Scrollbar::setTrackY(const std::shared_ptr<Element>& newTrackY) {
		if (newTrackY == nullptr) {
			trackY = nullptr;
			return;
		}

		trackY = Clickable::New(ctx, {
//			->onClick([this] (const std::shared_ptr<MouseButtonEvent>& event, Position position) {
//                float positionY = (position.y / this->child->getHeight()) * this->child->getScrollHeight();
//                this->child->setScrollTop(positionY - (this->child->getHeight() / 2));
//                return EventCallbackResponse::StopPropagation;
//			})
			.child = newTrackY,
		});
	}

	void Scrollbar::setThumbX(const std::shared_ptr<Element>& newThumbX) {
		if (newThumbX == nullptr) {
			thumbX = nullptr;
			return;
		}

		thumbX = Draggable::New(ctx, {
			.onMove = [this](Position p, Position ap, Position diff) {
				auto scrollDiff = diff.x * child->getScrollSize().width / child->getSize().width;
				child->setScrollLeft(child->getScrollLeft() + scrollDiff);
			},
			.child = newThumbX,
		});
	}

	void Scrollbar::setThumbY(const std::shared_ptr<Element>& newThumbY) {
		if (newThumbY == nullptr) {
			thumbY = nullptr;
			return;
		}

		thumbY = Draggable::New(ctx, {
			.onMove = [this](Position p, Position ap, Position diff) {
				auto scrollDiff = diff.y * child->getScrollSize().height / child->getSize().height;
				child->setScrollTop(child->getScrollTop() + scrollDiff);
			},
			.child = newThumbY,
		});
	}

	bool Scrollbar::showTrackX() const {
		return trackX != nullptr
			&& child != nullptr
			&& child->isHorizontalScroll()
			&& (visible == ScrollbarableVisible::Always || child->getScrollSize().width > child->getSize().width);
	}

	bool Scrollbar::showTrackY() const {
		return trackY != nullptr
			&& child != nullptr
			&& child->isVerticalScroll()
			&& (visible == ScrollbarableVisible::Always || child->getScrollSize().height > child->getSize().height);
	}

	Size Scrollbar::getTrackXSize(const Boundaries& boundaries) const {
		if (trackX == nullptr) {
			return ZeroSize;
		}

		Boundaries trackXBoundaries = {
			.min = { .width = boundaries.max.width, .height = 0 },
			.max = boundaries.max,
		};

		return trackX->getSize(trackXBoundaries);
	}

	Size Scrollbar::getTrackYSize(const Boundaries& boundaries) const {
		if (trackY == nullptr) {
			return ZeroSize;
		}

		Boundaries trackYBoundaries = {
			.min = { .width = 0, .height = boundaries.max.height },
			.max = boundaries.max,
		};

		return trackY->getSize(trackYBoundaries);
	}

	Size Scrollbar::getSize(const Boundaries& boundaries) {
		if (child == nullptr) {
			return boundaries.max;
		}

		auto trackXSize = showTrackX() && position == ScrollbarablePosition::InContent
						  ? getTrackXSize(boundaries)
						  : ZeroSize;

		auto trackYSize = showTrackY() && position == ScrollbarablePosition::InContent
						  ? getTrackYSize(boundaries)
						  : ZeroSize;

		Boundaries childBoundaries = {
			.min = {
				.width = boundaries.min.width - trackYSize.width,
				.height = boundaries.min.height - trackXSize.height
			},
			.max = {
				.width = boundaries.max.width - trackYSize.width,
				.height = boundaries.max.height - trackXSize.height
			}
		};

		Size childSize = child->getSize(childBoundaries);

		Size childSizeWithTrack = {
			.width = childSize.width + trackYSize.width,
			.height = childSize.height + trackXSize.height
		};

		return fitSizeInBoundaries(childSizeWithTrack, boundaries);
	}

	std::vector<ElementWithRect> Scrollbar::getChildren(const ElementRect& rect) {
		if (child == nullptr) {
			return {};
		}

		std::vector<ElementWithRect> children;

		auto trackXSize = showTrackX()
						  ? getTrackXSize({ .min = ZeroSize, .max = rect.size })
						  : ZeroSize;

		auto trackYSize = showTrackY()
						  ? getTrackYSize({ .min = ZeroSize, .max = rect.size })
						  : ZeroSize;

		Size childSize = {
			.width = rect.size.width - (position == ScrollbarablePosition::InContent ? trackYSize.width : 0),
			.height = rect.size.height - (position == ScrollbarablePosition::InContent ? trackXSize.height : 0)
		};

		Rect childRect = {
			.size = childSize,
			.position = { .x = 0, .y = 0 }
		};

		auto childAsElement = std::dynamic_pointer_cast<Element>(child);
		ElementWithRect childElementRect(childAsElement, childRect);
		children.push_back(childElementRect);

		if (showTrackX()) {
			Position trackXPosition = {
				.x = 0,
				.y = rect.size.height - trackXSize.height,
			};

			Rect trackXRect = { .size = trackXSize, .position = trackXPosition };
			ElementWithRect trackXElementRect(trackX, trackXRect);
			children.push_back(trackXElementRect);

			if (thumbX) {
				Size thumbXSize = {
					.width = (child->getSize().width / child->getScrollSize().width) * trackXSize.width,
					.height = trackXSize.height,
				};

				Position thumbXPosition = {
					.x = 0,
					.y = trackXPosition.y,
				};
			}
		}

		if (showTrackY()) {
			Position trackYPosition = {
				.x = rect.size.width - trackYSize.width,
				.y = 0,
			};

			Rect trackYRect = { .size = trackYSize, .position = trackYPosition };
			ElementWithRect trackYElementRect(trackY, trackYRect);
			children.push_back(trackYElementRect);
		}

		return children;
	}
}

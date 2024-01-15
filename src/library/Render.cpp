//
// Created by noartem 21 18.05.2022.
//

#include "Render.h"

#include <algorithm>

namespace elementor {
	bool Rect::contains(float x, float y) const {
		return (
			position.x < x &&
				position.x + size.width > x &&
				position.y < y &&
				position.y + size.height > y
		);
	}

	bool Rect::contains(Position point) const {
		return contains(point.x, point.y);
	}

	Rect unionOfRects(const Rect& a, const Rect& b) {
		Rect result{};
		result.position.x = std::max(a.position.x, b.position.x);
		result.position.y = std::max(a.position.y, b.position.y);
		result.size.width = std::max(
			std::min(a.position.x + a.size.width, b.position.x + b.size.width) - result.position.x, 0.0f
		);
		result.size.height = std::max(
			std::min(a.position.y + a.size.height, b.position.y + b.size.height) - result.position.y, 0.0f
		);
		return result;
	}

	bool ElementRect::visibleContains(float x, float y) const {
		return (
			visiblePosition.x < x &&
				visiblePosition.x + visibleSize.width > x &&
				visiblePosition.y < y &&
				visiblePosition.y + visibleSize.height > y
		);
	}

	bool ElementRect::visibleContains(Position point) const {
		return visibleContains(point.x, point.y);
	}

	Position ElementRect::absolutePositionToContained(Position absolutePosition) const {
		return {
			.x = absolutePosition.x - position.x,
			.y = absolutePosition.y - position.y,
		};
	}

	Size fitSizeInBoundaries(Size size, Boundaries boundaries) {
		return {
			.width = std::min(std::max(size.width, boundaries.min.width), boundaries.max.width),
			.height = std::min(std::max(size.height, boundaries.min.height), boundaries.max.height)
		};
	}
}

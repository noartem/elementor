//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_RENDER_H
#define ELEMENTOR_RENDER_H

#include <limits>

namespace elementor {

	struct Position {
		float x;
		float y;
	};

	struct Size {
		float width;
		float height;
	};

	struct Boundaries {
		Size min;
		Size max;
	};

	struct Rect {
		Size size;
		Position position;

		[[nodiscard]] bool contains(float x, float y) const;

		[[nodiscard]] bool contains(Position point) const;
	};

	Rect unionOfRects(const Rect& a, const Rect& b);

	struct ElementRect : Rect {
		Size visibleSize;
		Position visiblePosition;
		Position inParentPosition;

		[[nodiscard]] bool visibleContains(float x, float y) const;

		[[nodiscard]] bool visibleContains(Position point) const;

		[[nodiscard]] Position absolutePositionToContained(Position absolutePosition) const;
	};

	Size fitSizeInBoundaries(Size size, Boundaries boundaries);

	constexpr float Infinity = std::numeric_limits<float>::infinity();

	constexpr Size ZeroSize = { 0, 0 };

	constexpr Size InfiniteSize = { Infinity, Infinity };

	constexpr Boundaries InfiniteBoundaries = {
		.min = ZeroSize,
		.max = InfiniteSize
	};
}

#endif //ELEMENTOR_RENDER_H
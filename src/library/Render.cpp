//
// Created by noartem 21 18.05.2022.
//

#include "Render.h"

#include <algorithm>

namespace elementor {
    bool Rect::contains(float x, float y) {
        return (
                position.x < x &&
                position.x + size.width > x &&
                position.y < y &&
                position.y + size.height > y
        );
    }

    bool Rect::contains(Position point) {
        return contains(point.x, point.y);
    }

    bool ElementRect::contains(float x, float y) {
        return (
                position.x < x &&
                position.x + size.width > x &&
                position.y < y &&
                position.y + size.height > y
        );
    }

    bool ElementRect::contains(Position point) {
        return contains(point.x, point.y);
    }

    bool ElementRect::visibleContains(float x, float y) {
        return (
                visiblePosition.x < x &&
                visiblePosition.x + visibleSize.width > x &&
                visiblePosition.y < y &&
                visiblePosition.y + visibleSize.height > y
        );

    }

    bool ElementRect::visibleContains(Position point) {
        return visibleContains(point.x, point.y);
    }

    Position ElementRect::absolutePositionToContained(Position absolutePosition) {
        return {
                absolutePosition.x - position.x,
                absolutePosition.y - position.y,
        };
    }

    Size fitSizeInBoundaries(Size size, Boundaries boundaries) {
        float width = std::min(std::max(size.width, boundaries.min.width), boundaries.max.width);
        float height = std::min(std::max(size.height, boundaries.min.height), boundaries.max.height);
        return {width, height};
    }
}

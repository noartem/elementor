//
// Created by noartem 21 18.05.2022.
//

#include "Render.h"

namespace elementor {
    bool ElementRect::contains(float x, float y) {
        return (
            this->position.x < x &&
            this->position.x + this->size.width > x &&
            this->position.y < y &&
            this->position.y + this->size.height > y
        );
    }

    bool ElementRect::contains(int x, int y) {
        return this->contains((float) x, (float) y);
    }

    bool ElementRect::contains(Position point) {
        return this->contains(point.x, point.y);
    }

    bool ElementRect::visibleContains(float x, float y) {
        return (
            this->position.x < x &&
            this->position.x + this->visibleSize.width > x &&
            this->position.y < y &&
            this->position.y + this->visibleSize.height > y
        );
    }

    bool ElementRect::visibleContains(int x, int y) {
        return this->visibleContains((float) x, (float) y);
    }

    bool ElementRect::visibleContains(Position point) {
        return this->visibleContains(point.x, point.y);
    }

    Position ElementRect::absolutePositionToContained(Position absoulutePosition) {
        return {
            absoulutePosition.x - this->position.x,
            absoulutePosition.y - this->position.y,
        };
    }
}

//
// Created by noartem 21 18.05.2022.
//

#include "Render.h"

namespace elementor {
    bool Rect::contains(float x, float y) {
        return (
            this->position.x < x &&
            this->position.x + this->size.width > x &&
            this->position.y < y &&
            this->position.y + this->size.height > y
        );
    }

    bool Rect::contains(int x, int y) {
        return this->contains((float) x, (float) y);
    }

    bool Rect::contains(Position point) {
        return this->contains(point.x, point.y);
    }
}

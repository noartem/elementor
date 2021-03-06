//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_RENDER_H
#define ELEMENTOR_RENDER_H

namespace elementor {
    #define ZERO (float) 0

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
    };

    class ElementRect {
    public:
        Position position;
        Position inParentPosition;
        Size size;
        Size visibleSize;

        bool contains(float x, float y);

        bool contains(Position point);

        bool visibleContains(float x, float y);

        bool visibleContains(Position point);

        Position absolutePositionToContained(Position absolutePosition);
    };
}

#endif //ELEMENTOR_RENDER_H
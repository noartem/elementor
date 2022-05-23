//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_RENDER_H
#define ELEMENTOR_RENDER_H

namespace elementor {
    struct Position {
        int x;
        int y;
    };

    struct Size {
        int width;
        int height;
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

        bool contains(int x, int y);

        bool contains(Position point);

        bool visibleContains(float x, float y);

        bool visibleContains(int x, int y);

        bool visibleContains(Position point);
    };
}

#endif //ELEMENTOR_RENDER_H
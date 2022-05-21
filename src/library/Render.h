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

    class Rect {
        public:
            Size size;
            Position position;

            bool contains(float x, float y);

            bool contains(int x, int y);

            bool contains(Position point);
    };
}

#endif //ELEMENTOR_RENDER_H
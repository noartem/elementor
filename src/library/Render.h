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
}

#endif //ELEMENTOR_RENDER_H
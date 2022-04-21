//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_RENDER_H
#define ELEMENTOR_RENDER_H

namespace elementor {
    struct RenderPosition {
        int x;
        int y;
    };

    struct RenderSize {
        int width;
        int height;
    };

    struct RenderBoundaries {
        RenderSize min;
        RenderSize max;
    };
}

#endif //ELEMENTOR_RENDER_H
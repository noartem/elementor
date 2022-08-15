//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_GLPERFOMANCE_H
#define ELEMENTOR_GL_GLPERFOMANCE_H

#include "../Element.h"

#include "GLFW/glfw3.h"

namespace elementor {
    class GLPerfomance : public Perfomance {
    public:
        double getFPS() override;
        void incrementFramesCount();

    private:
        double framesLastTime;
        double framesCount;
        double lastFPS;
    };
};

#endif //ELEMENTOR_GL_GLPERFOMANCE_H

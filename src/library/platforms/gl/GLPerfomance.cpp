//
// Created by noartem on 15.08.2022.
//

#include "GLPerfomance.h"

namespace elementor::platforms::gl {
    void GLPerfomance::incrementFramesCount() {
        this->framesCount++;

        double now = glfwGetTime();
        if ((now - this->framesLastTime) >= 1) {
            this->lastFPS = this->framesCount;
            this->framesLastTime = now;
            this->framesCount = 0;
        }
    }

    double GLPerfomance::getFPS() {
        return this->lastFPS;
    }
}


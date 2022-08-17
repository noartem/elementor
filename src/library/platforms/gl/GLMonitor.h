//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_GLMONITOR_H
#define ELEMENTOR_GL_GLMONITOR_H

#include "../../Element.h"

#include "GLFW/glfw3.h"

namespace elementor {
    class GLMonitor : public Monitor {
    public:
        GLMonitor(GLFWmonitor *monitor);
        Size getSize() override;
        Size getPhysicalSize() override;

    private:
        Size size;
        Size physicalSize;
    };
};

#endif //ELEMENTOR_GL_GLMONITOR_H

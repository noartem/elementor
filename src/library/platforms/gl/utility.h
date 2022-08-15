//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_UTILITY_H
#define ELEMENTOR_GL_UTILITY_H

#include "../../Render.h"

#include "GLFW/glfw3.h"

namespace elementor {
    Size getWindowSize(GLFWwindow *window);

    Position getWindowPosition(GLFWwindow *window);

    Rect getWindowRect(GLFWwindow *window);

    Size getMonitorSize(GLFWmonitor *monitor);

    Size getMonitorPhysicalSize(GLFWmonitor *monitor);

    Position getMonitorPosition(GLFWmonitor *monitor);

    Rect getMonitorRect(GLFWmonitor *monitor);

    GLFWmonitor* getWindowMonitor(GLFWwindow* window);
};


#endif //ELEMENTOR_GL_UTILITY_H

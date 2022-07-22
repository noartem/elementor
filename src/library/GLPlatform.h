//
// Created by noartem on 14.04.2022.
//

#ifndef ELEMENTOR_GLPLATFORM_H
#define ELEMENTOR_GLPLATFORM_H

#include "Application.h"

#include "GLFW/glfw3.h"
#include "include/gpu/GrDirectContext.h"
#include <optional>

namespace elementor {
    class GLClipboard : public Clipboard {
    public:
        GLClipboard(GLFWwindow *window);
        void set(std::string value) override;
        std::string get() override;

    private:
        GLFWwindow *window;
    };

    class GLPlatform {
    public:
        std::string title;
        Size size;
        std::optional <Size> minSize;
        std::optional <Size> maxSize;
        Application *application;

        int run();
        void forceUpdate();

    private:
        GLFWwindow *window;
        GLFWmonitor *monitor;
        SkSurface *skiaSurface;
        SkCanvas *skiaCanvas;
        GrDirectContext *skiaContext;
        ApplicationContext applicationContext;

        void refresh();
        void draw();

        Size getWindowSize();
        Size getMonitorPhysicalSize();
        Size getMonitorSize();
        Clipboard *makeClipboard();
        float calcMonitorPixelScale(Size monitorPhysicalSize);

        void onMouseButton(int button, int action, int mods);
        void onKeyboard(int key, int scancode, int action, int mods);
        void onChar(unsigned int codepoint);
        void onMouseMove(double x, double y);
        void onScroll(double xOffset, double yOffset);
    };
};


#endif //ELEMENTOR_GLPLATFORM_H
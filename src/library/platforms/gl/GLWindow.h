//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_GLWINDOW_H
#define ELEMENTOR_GL_GLWINDOW_H

#include "../../Application.h"
#include "GLCursor.h"
#include "GLMonitor.h"

#define SK_GL
#include "GLFW/glfw3.h"
#include "include/gpu/GrDirectContext.h"

namespace elementor {
    class GLWindow : public Window {
    public:
        GLWindow(ApplicationContext *applicationContext);

        void draw();
        void refresh();
        void updateMonitor();

        Element *getRoot() override;
        void setRoot(Element *root) override;

        void setTitle(std::string title) override;
        std::string getTitle() override;

        Size getSize() override;
        void setSize(Size size) override;
        std::optional<Size> getMinSize() override;
        std::optional<Size> getMaxSize() override;
        void setMinSize(Size size) override;
        void setMaxSize(Size size) override;
        void updateWindowSizeLimits();

        Position getPosition() override;
        void setPosition(Position Position) override;

        bool shouldClose();
        void close() override;

        Cursor *getCursor() override;
        Monitor *getMonitor() override;

    private:
        Application *application;

        Element *root;
        std::string title;
        std::optional<Size> minSize;
        std::optional<Size> maxSize;

        GLFWwindow *glWindow;
        GrDirectContext *skContext;
        SkSurface *skSurface;
        SkCanvas *skCanvas;

        GLFWmonitor *glMonitor;
        GLMonitor *monitor;

        ApplicationContext *applicationContext;
        GLCursor *cursor;

        void onMouseButton(int button, int action, int mods);
        void onKeyboard(int key, int scancode, int action, int mods);
        void onChar(unsigned int codepoint);
        void onMouseMove(double x, double y);
        void onScroll(double xOffset, double yOffset);
    };
};


#endif //ELEMENTOR_GL_GLWINDOW_H

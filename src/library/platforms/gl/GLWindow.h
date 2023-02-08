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
    class GLWindow : public Window, std::enable_shared_from_this<GLWindow> {
    public:
        GLWindow(std::shared_ptr<ApplicationContext> applicationContext, Size size);

        ~GLWindow();

        void draw();

        std::shared_ptr<Element> getRoot() override;
        void setRoot(std::shared_ptr<Element> newRoot) override;

        void setTitle(std::string newTitle) override;
        std::string getTitle() override;

        Size getSize() override;
        void setSize(Size size) override;

        std::optional<Size> getMinSize() override;
        void setMinSize(std::optional<Size> size) override;
        void setMinSize(Size size) override;

        std::optional<Size> getMaxSize() override;
        void setMaxSize(std::optional<Size> size) override;
        void setMaxSize(Size size) override;

        Position getPosition() override;
        void setPosition(Position Position) override;

        std::shared_ptr<Cursor> getCursor() override;

        std::shared_ptr<Monitor> getMonitor() override;

        void close() override;

        void onClose(std::function<void ()> callback);

        void setUserPointer(std::shared_ptr<void> pointer) override;
        std::shared_ptr<void> getUserPointer() override;

    private:
        std::shared_ptr<Application> application;

        std::shared_ptr<Element> root;
        std::string title;
        std::optional<Size> minSize;
        std::optional<Size> maxSize;

        GLFWwindow *glWindow;
        GrDirectContext *skContext;
        sk_sp<SkSurface> skSurface;
        SkCanvas *skCanvas{};
        void refresh();

        std::shared_ptr<GLMonitor> monitor;

        std::shared_ptr<ApplicationContext> applicationContext;
        std::shared_ptr<GLCursor> cursor;

        std::shared_ptr<void> userPointer;

        void updateWindowSizeLimits();

        void onMouseButton(int button, int action, int mods);
        void onKeyboard(int key, int scancode, int action, int mods);
        void onChar(unsigned int codepoint);
        void onMouseMove(double x, double y);
        void onScroll(double xOffset, double yOffset);

        std::function<void ()> callbackClose;
    };
};


#endif //ELEMENTOR_GL_GLWINDOW_H

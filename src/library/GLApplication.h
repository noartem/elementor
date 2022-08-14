//
// Created by noartem on 14.04.2022.
//

#ifndef ELEMENTOR_GLPLATFORM_H
#define ELEMENTOR_GLPLATFORM_H

#include "Application.h"

#include "GLFW/glfw3.h"
#include "include/gpu/GrDirectContext.h"
#include <modules/skparagraph/include/TypefaceFontProvider.h>

namespace sktextlayout = skia::textlayout;

namespace elementor {
    class GLClipboard;
    class GLCursor;
    class GLPerfomance;
    class GLFontManager;
    class GLWindow;
    class GLApplicationContext;

    class GLApplication {
    public:
        GLApplication();

        void run();
        void requestNextFrame(std::function<void ()> callback);

        GLWindow *makeWindow();

        GLClipboard *getClipboard();
        GLPerfomance *getPerfomance();
        GLFontManager *getFontManager();
        sk_sp<SkFontMgr> getSkFontManager();

    private:
        GLClipboard *clipboard;
        GLFontManager *fontManager;
        GLPerfomance *perfomance;

        ApplicationContext *applicationContext;

        std::vector<GLWindow *> windows;

        std::vector<std::function<void ()>> rnfNextQueue;
        std::vector<std::function<void ()>> rnfCurrentQueue;
        void applyRnfQueue();
    };

    class GLMonitor : public Monitor {
    public:
        GLMonitor(GLFWmonitor *monitor);
        Size getSize() override;
        Size getPhysicalSize() override;
        float getPixelScale() override;
        void setPixelScale(float scale) override;

    private:
        Size size;
        Size physicalSize;
        float pixelScale;
    };

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

    class GLApplicationContext : public ApplicationContext {
    public:
        GLApplicationContext(GLApplication *application);

        Clipboard *getClipboard() override;
        Perfomance *getPerfomance() override;
        sk_sp<SkFontMgr> getSkFontManager() override;
        void requestNextFrame(std::function<void ()> callback) override;

    private:
        GLApplication *application;
    };

    class GLClipboard : public Clipboard {
    public:
        void set(std::string value) override;
        std::string get() override;
    };

    class GLCursor : public Cursor {
    public:
        GLCursor(GLFWwindow *window, ApplicationContext *ctx);
        void set(CursorShape shape) override;
        CursorShape get() override;

    private:
        ApplicationContext *ctx;
        GLFWwindow *window;
        GLFWcursor *cursor;
        CursorShape currentShape = CursorShape::Default;
        CursorShape appliedShape = CursorShape::Default;

        void updateCursor();
    };

    class GLPerfomance : public Perfomance {
    public:
        double getFPS() override;
        void incrementFramesCount();

    private:
        double framesLastTime;
        double framesCount;
        double lastFPS;
    };

    class GLFontManager {
    public:
        GLFontManager();
        sk_sp<SkFontMgr> getSkFontManager();
        void registerFontFromSkData(sk_sp<SkData> data);
        void registerFontFromPath(std::string path);

    private:
        sk_sp<sktextlayout::TypefaceFontProvider> skFontManager;
    };
};


#endif //ELEMENTOR_GLPLATFORM_H

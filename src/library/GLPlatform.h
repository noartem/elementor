//
// Created by noartem on 14.04.2022.
//

#ifndef ELEMENTOR_GLPLATFORM_H
#define ELEMENTOR_GLPLATFORM_H

#include "Application.h"

#include "GLFW/glfw3.h"
#include "include/gpu/GrDirectContext.h"
#include <modules/skparagraph/include/TypefaceFontProvider.h>
#include <optional>

namespace sktext = skia::textlayout;

namespace elementor {
    class GLApplicationContext;
    class GLClipboard;
    class GLCursor;
    class GLPerfomance;
    class GLFontManager;

    class GLPlatform {
    public:
        GLPlatform();

        std::string title;
        Size size;
        std::optional <Size> minSize;
        std::optional <Size> maxSize;
        Application *application;

        int run();
        void forceUpdate();
        void requestNextFrame(std::function<void ()> callback);

        GLFontManager *getFontManager();
        sk_sp<SkFontMgr> getSkFontManager();

    private:
        GLFWwindow *window;
        GLFWmonitor *monitor;
        SkSurface *skiaSurface;
        SkCanvas *skiaCanvas;
        GrDirectContext *skiaContext;

        GLFontManager *fontManager;

        void refresh();
        void draw();

        ApplicationContext *applicationContext;
        GLPerfomance *perfomance;
        Size getWindowSize();
        Size getMonitorPhysicalSize();
        Size getMonitorSize();
        Clipboard *makeClipboard();
        Cursor *makeCursor();
        float calcMonitorPixelScale(Size monitorPhysicalSize);
        ApplicationContext *makeApplicationContext();

        void onMouseButton(int button, int action, int mods);
        void onKeyboard(int key, int scancode, int action, int mods);
        void onChar(unsigned int codepoint);
        void onMouseMove(double x, double y);
        void onScroll(double xOffset, double yOffset);

        std::vector<std::function<void ()>> rnfNextQueue;
        std::vector<std::function<void ()>> rnfCurrentQueue;
        void applyRnfQueue();
    };

    class GLApplicationContext : public ApplicationContext {
    public:
        GLApplicationContext(GLPlatform *glPlatform);
        void requestNextFrame(std::function<void ()> callback) override;
        sk_sp<SkFontMgr> getSkFontManager() override;

    private:
        GLPlatform *platform;
    };

    class GLClipboard : public Clipboard {
    public:
        GLClipboard(GLFWwindow *window);
        void set(std::u32string value) override;
        std::u32string get() override;

    private:
        GLFWwindow *window;
    };

    class GLCursor : public Cursor {
    public:
        GLCursor(GLFWwindow *window, GLPlatform *platform);
        void set(CursorShape shape) override;

    private:
        GLFWwindow *window;
        GLFWcursor *cursor;
        GLPlatform *platform;
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
        sk_sp<sktext::TypefaceFontProvider> skFontManager;
    };
};


#endif //ELEMENTOR_GLPLATFORM_H

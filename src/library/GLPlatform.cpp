//
// Created by noartem on 14.04.2022.
//

#include "GLFW/glfw3.h"

#define SK_GL

#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include <include/core/SkTypeface.h>
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"

#include "GLPlatform.h"
#include "String.h"

#include <stdio.h>
#include <stdlib.h>

#define GL_RGBA8 0x8058

namespace elementor {
    GLPlatform::GLPlatform() {
        this->perfomance = new GLPerfomance();
        this->fontManager = new GLFontManager();
    }

    Size GLPlatform::getWindowSize() {
        int width, height;
        glfwGetFramebufferSize(this->window, &width, &height);
        return {(float) width, (float) height};
    }

    Size GLPlatform::getMonitorPhysicalSize() {
        int width, height;
        glfwGetMonitorPhysicalSize(this->monitor, &width, &height);
        return {(float) width, (float) height};
    }

    Size GLPlatform::getMonitorSize() {
        const GLFWvidmode* mode = glfwGetVideoMode(this->monitor);
        return {(float) mode->width, (float) mode->height};
    }

    float GLPlatform::calcMonitorPixelScale(Size monitorPhysicalSize) {
        Size monitorSize = this->getMonitorSize();
        return (monitorSize.width / monitorPhysicalSize.width) / DefaultMonitorScale;
    }

    ApplicationContext *GLPlatform::makeApplicationContext() {
        ApplicationContext *applicationContext = new GLApplicationContext(this);
        applicationContext->windowSize = this->getWindowSize();
        applicationContext->monitorPhysicalSize = this->getMonitorPhysicalSize();
        applicationContext->monitorPixelScale = this->calcMonitorPixelScale(applicationContext->monitorPhysicalSize);
        applicationContext->root = this->application->root;
        applicationContext->clipboard = this->makeClipboard();
        applicationContext->cursor = this->makeCursor();
        applicationContext->perfomance = this->perfomance;
        return applicationContext;
    }

    Clipboard *GLPlatform::makeClipboard() {
        return new GLClipboard(this->window);
    }

    Cursor *GLPlatform::makeCursor() {
        return new GLCursor(this->window, this);
    }

    void GLPlatform::refresh() {
        this->applicationContext = this->makeApplicationContext();

        if (this->skiaSurface) {
            delete this->skiaSurface;
        }

        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0;
        framebufferInfo.fFormat = GL_RGBA8;

        // create skia canvas
        GrBackendRenderTarget backendRenderTarget(this->applicationContext->windowSize.width, this->applicationContext->windowSize.height, 0, 0, framebufferInfo);
        this->skiaSurface = SkSurface::MakeFromBackendRenderTarget(this->skiaContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, kRGBA_8888_SkColorType, SkColorSpace::MakeSRGB(), nullptr).release();
        this->skiaCanvas = this->skiaSurface->getCanvas();
    }

    void GLPlatform::draw() {
        this->applyRnfQueue();

        this->skiaCanvas->clear(SK_ColorBLACK);
        this->application->draw(this->applicationContext, this->skiaCanvas);

        this->skiaContext->flush();
        glfwSwapBuffers(this->window);

        this->perfomance->incrementFramesCount();
    }

    MouseButton mapIntToMouseButton(int button) {
        switch (button) {
            case 0:
                return MouseButton::Left;
            case 1:
                return MouseButton::Right;
            case 2:
                return MouseButton::Middle;
            case 3:
                return MouseButton::Back;
            case 4:
                return MouseButton::Forward;
            default:
                return MouseButton::Left;
        }
    }

    KeyAction mapIntToKeyAction(int action) {
        switch (action) {
            case 0:
                return KeyAction::Release;
            case 1:
                return KeyAction::Press;
            case 2:
                return KeyAction::Repeat;
            default:
                return KeyAction::Release;
        }
    }

    KeyMod mapIntToKeyMod(int mod) {
        switch (mod) {
            case 1:
                return KeyMod::Shift;
            case 2:
                return KeyMod::Control;
            case 4:
                return KeyMod::Alt;
            case 8:
                return KeyMod::Super;
            case 10:
                return KeyMod::CapsLock;
            case 20:
                return KeyMod::NumLock;
            default:
                return KeyMod::None;
        }
    }

    KeyboardKey mapIntToKeyboardKey(int key) {
        switch (key) {
            case 32:
                return KeyboardKey::Space;
            case 39:
                return KeyboardKey::Apostraphe;
            case 44:
                return KeyboardKey::Comma;
            case 45:
                return KeyboardKey::Minus;
            case 46:
                return KeyboardKey::Period;
            case 47:
                return KeyboardKey::Slash;
            case 48:
                return KeyboardKey::Number0;
            case 161:
                return KeyboardKey::Number1World;
            case 49:
                return KeyboardKey::Number1;
            case 162:
                return KeyboardKey::Number2World;
            case 50:
                return KeyboardKey::Number2;
            case 51:
                return KeyboardKey::Number3;
            case 52:
                return KeyboardKey::Number4;
            case 53:
                return KeyboardKey::Number5;
            case 54:
                return KeyboardKey::Number6;
            case 55:
                return KeyboardKey::Number7;
            case 56:
                return KeyboardKey::Number8;
            case 57:
                return KeyboardKey::Number9;
            case 59:
                return KeyboardKey::Semicolon;
            case 61:
                return KeyboardKey::Equal;
            case 65:
                return KeyboardKey::A;
            case 66:
                return KeyboardKey::B;
            case 67:
                return KeyboardKey::C;
            case 68:
                return KeyboardKey::D;
            case 69:
                return KeyboardKey::E;
            case 70:
                return KeyboardKey::F;
            case 71:
                return KeyboardKey::G;
            case 72:
                return KeyboardKey::H;
            case 73:
                return KeyboardKey::I;
            case 74:
                return KeyboardKey::J;
            case 75:
                return KeyboardKey::K;
            case 76:
                return KeyboardKey::L;
            case 77:
                return KeyboardKey::M;
            case 78:
                return KeyboardKey::N;
            case 79:
                return KeyboardKey::O;
            case 80:
                return KeyboardKey::P;
            case 81:
                return KeyboardKey::Q;
            case 82:
                return KeyboardKey::R;
            case 83:
                return KeyboardKey::S;
            case 84:
                return KeyboardKey::T;
            case 85:
                return KeyboardKey::U;
            case 86:
                return KeyboardKey::V;
            case 87:
                return KeyboardKey::W;
            case 88:
                return KeyboardKey::X;
            case 89:
                return KeyboardKey::Y;
            case 90:
                return KeyboardKey::Z;
            case 91:
                return KeyboardKey::LeftBracket;
            case 92:
                return KeyboardKey::Backslash;
            case 93:
                return KeyboardKey::RightBracket;
            case 96:
                return KeyboardKey::GraveAccent;
            case 256:
                return KeyboardKey::Escape;
            case 257:
                return KeyboardKey::Enter;
            case 258:
                return KeyboardKey::Tab;
            case 259:
                return KeyboardKey::Backspace;
            case 260:
                return KeyboardKey::Insert;
            case 261:
                return KeyboardKey::Delete;
            case 262:
                return KeyboardKey::Right;
            case 263:
                return KeyboardKey::Left;
            case 264:
                return KeyboardKey::Down;
            case 265:
                return KeyboardKey::Up;
            case 266:
                return KeyboardKey::PageUp;
            case 267:
                return KeyboardKey::PageDown;
            case 268:
                return KeyboardKey::Home;
            case 269:
                return KeyboardKey::End;
            case 280:
                return KeyboardKey::CapsLock;
            case 281:
                return KeyboardKey::ScrollLock;
            case 282:
                return KeyboardKey::NumLock;
            case 283:
                return KeyboardKey::PrintScreen;
            case 284:
                return KeyboardKey::Pause;
            case 290:
                return KeyboardKey::F1;
            case 291:
                return KeyboardKey::F2;
            case 292:
                return KeyboardKey::F3;
            case 293:
                return KeyboardKey::F4;
            case 294:
                return KeyboardKey::F5;
            case 295:
                return KeyboardKey::F6;
            case 296:
                return KeyboardKey::F7;
            case 297:
                return KeyboardKey::F8;
            case 298:
                return KeyboardKey::F9;
            case 299:
                return KeyboardKey::F10;
            case 300:
                return KeyboardKey::F11;
            case 301:
                return KeyboardKey::F12;
            case 302:
                return KeyboardKey::F13;
            case 303:
                return KeyboardKey::F14;
            case 304:
                return KeyboardKey::F15;
            case 305:
                return KeyboardKey::F16;
            case 306:
                return KeyboardKey::F17;
            case 307:
                return KeyboardKey::F18;
            case 308:
                return KeyboardKey::F19;
            case 309:
                return KeyboardKey::F20;
            case 310:
                return KeyboardKey::F21;
            case 311:
                return KeyboardKey::F22;
            case 312:
                return KeyboardKey::F23;
            case 313:
                return KeyboardKey::F24;
            case 314:
                return KeyboardKey::F25;
            case 320:
                return KeyboardKey::KP0;
            case 321:
                return KeyboardKey::KP1;
            case 322:
                return KeyboardKey::KP2;
            case 323:
                return KeyboardKey::KP3;
            case 324:
                return KeyboardKey::KP4;
            case 325:
                return KeyboardKey::KP5;
            case 326:
                return KeyboardKey::KP6;
            case 327:
                return KeyboardKey::KP7;
            case 328:
                return KeyboardKey::KP8;
            case 329:
                return KeyboardKey::KP9;
            case 330:
                return KeyboardKey::KPDecimal;
            case 331:
                return KeyboardKey::KPDivide;
            case 332:
                return KeyboardKey::KPMultiply;
            case 333:
                return KeyboardKey::KPSubtract;
            case 334:
                return KeyboardKey::KPAdd;
            case 335:
                return KeyboardKey::KPEnter;
            case 336:
                return KeyboardKey::KPEqual;
            case 340:
                return KeyboardKey::LeftShift;
            case 341:
                return KeyboardKey::LeftControl;
            case 342:
                return KeyboardKey::LeftAlt;
            case 343:
                return KeyboardKey::LeftSuper;
            case 344:
                return KeyboardKey::RightShift;
            case 345:
                return KeyboardKey::RightControl;
            case 346:
                return KeyboardKey::RightAlt;
            case 347:
                return KeyboardKey::RightSuper;
            case 348:
                return KeyboardKey::Menu;
            default:
                return KeyboardKey::Unknow;
        }
    }

    void GLPlatform::onMouseButton(int button, int action, int mods) {
        EventMouseButton *event = new EventMouseButton();
        event->button = mapIntToMouseButton(button);
        event->action = mapIntToKeyAction(action);
        event->mod = mapIntToKeyMod(mods);

        this->application->dispatchEvent(event);
    }

    void GLPlatform::onKeyboard(int key, int scancode, int action, int mods) {
        EventKeyboard *event = new EventKeyboard();
        event->key = mapIntToKeyboardKey(key);
        event->scancode = scancode;
        event->action = mapIntToKeyAction(action);
        event->mod = mapIntToKeyMod(mods);

        this->application->dispatchEvent(event);
    }

    void GLPlatform::onChar(unsigned int codepoint) {
        EventChar *event = new EventChar();
        event->value = codepoint;

        this->application->dispatchEvent(event);
    }

    void GLPlatform::onMouseMove(double x, double y) {
        EventMouseMove *event = new EventMouseMove();
        event->x = x;
        event->y = y;

        this->application->dispatchEvent(event);
    }

    void GLPlatform::onScroll(double xOffset, double yOffset) {
        EventScroll *event = new EventScroll();
        event->xOffset = xOffset;
        event->yOffset = yOffset;

        this->application->dispatchEvent(event);
    }

    GLPlatform *getWindowGLPlatform(GLFWwindow *window) {
        return static_cast<GLPlatform *>(glfwGetWindowUserPointer(window));
    }

    int GLPlatform::run() {
        if (!glfwInit()) {
            exit(EXIT_FAILURE);
        }

        glfwSetErrorCallback([] (int error, const char *description) {
            fputs(description, stderr);
        });

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_STENCIL_BITS, 0);
        glfwWindowHint(GLFW_ALPHA_BITS, 0);
        glfwWindowHint(GLFW_DEPTH_BITS, 0);

        GLFWwindow *window = glfwCreateWindow(this->size.width, this->size.height, this->title.c_str(), NULL, NULL);
        if (!window) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        this->window = window;

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetWindowUserPointer(window, this);

        if (this->minSize && this->maxSize) {
            glfwSetWindowSizeLimits(window, this->minSize->width, this->minSize->height, this->maxSize->width, this->maxSize->height);
        } else if (this->minSize && !this->maxSize) {
            glfwSetWindowSizeLimits(window, this->minSize->width, this->minSize->height, GLFW_DONT_CARE, GLFW_DONT_CARE);
        } else if (!this->minSize && this->maxSize) {
            glfwSetWindowSizeLimits(window, GLFW_DONT_CARE, GLFW_DONT_CARE, this->maxSize->width, this->maxSize->height);
        }

        glfwSetKeyCallback(window, [] (GLFWwindow *window, int key, int scancode, int action, int mods) {
            GLPlatform *platform = getWindowGLPlatform(window);
            platform->onKeyboard(key, scancode, action, mods);
        });

        glfwSetCharCallback(window, [] (GLFWwindow *window, unsigned int codepoint) {
            GLPlatform *platform = getWindowGLPlatform(window);
            platform->onChar(codepoint);
        });

        glfwSetMouseButtonCallback(window, [] (GLFWwindow* window, int button, int action, int mods) {
            GLPlatform *platform = getWindowGLPlatform(window);
            platform->onMouseButton(button, action, mods);
        });

        glfwSetCursorPosCallback(window, [] (GLFWwindow* window, double x, double y) {
            GLPlatform *platform = getWindowGLPlatform(window);
            platform->onMouseMove(x, y);
        });

        glfwSetScrollCallback(window, [] (GLFWwindow* window, double xOffset, double yOffset) {
            GLPlatform *platform = getWindowGLPlatform(window);
            platform->onScroll(xOffset, yOffset);
        });

        GLFWmonitor* monitor = glfwGetWindowMonitor(window);
        if (monitor == NULL) {
            monitor = glfwGetPrimaryMonitor();
        }
        this->monitor = monitor;

        // init skia
        auto interface = GrGLMakeNativeInterface();
        this->skiaContext = GrDirectContext::MakeGL(interface).release();

        glfwSetWindowRefreshCallback(window, [] (GLFWwindow* window) {
            GLPlatform *platform = getWindowGLPlatform(window);
            platform->refresh();
            platform->draw();
        });

        while (!glfwWindowShouldClose(window)) {
            glfwWaitEvents();
            this->draw();
        }

        // cleanup skia
        if (this->skiaSurface) delete this->skiaSurface;
        if (this->skiaContext) delete this->skiaContext;

        // cleanup glfw
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

    void GLPlatform::requestNextFrame(std::function<void ()> callback) {
        glfwPostEmptyEvent();
        this->rnfNextQueue.push_back(callback);
    }

    void GLPlatform::applyRnfQueue() {
        if (this->rnfCurrentQueue.empty() && this->rnfNextQueue.empty() > 0) {
            return;
        }

        for (std::function<void ()> callback : this->rnfCurrentQueue) {
            callback();
        }

        this->rnfCurrentQueue = this->rnfNextQueue;
        this->rnfNextQueue = {};
    }

    GLFontManager *GLPlatform::getFontManager() {
        return this->fontManager;
    }

    sk_sp<SkFontMgr> GLPlatform::getSkFontManager() {
        return this->fontManager->getSkFontManager();
    }

    GLApplicationContext::GLApplicationContext(GLPlatform *platform) {
        this->platform = platform;
    }

    void GLApplicationContext::requestNextFrame(std::function<void ()> callback) {
        this->platform->requestNextFrame(callback);
    }

    sk_sp<SkFontMgr> GLApplicationContext::getSkFontManager() {
        return this->platform->getSkFontManager();
    }

    GLClipboard::GLClipboard(GLFWwindow *window) {
        this->window = window;
    }

    void GLClipboard::set(std::string value) {
        glfwSetClipboardString(this->window, value.c_str());
    }

    std::string GLClipboard::get() {
        return glfwGetClipboardString(window);
    }

    GLCursor::GLCursor(GLFWwindow *window, GLPlatform *platform) {
        this->window = window;
        this->platform = platform;
    }

    unsigned int mapCursorShape(CursorShape shape) {
        switch (shape) {
            case CursorShape::Default:
            case CursorShape::Arrow:
                return GLFW_ARROW_CURSOR;
            case CursorShape::IBeam:
                return GLFW_IBEAM_CURSOR;
            case CursorShape::Crosshair:
                return GLFW_CROSSHAIR_CURSOR;
            case CursorShape::Hand:
                return GLFW_HAND_CURSOR;
            case CursorShape::HorizontalResize:
                return GLFW_HRESIZE_CURSOR;
            case CursorShape::VerticalResize:
                return GLFW_VRESIZE_CURSOR;
        }
    }

    void GLCursor::updateCursor() {
        if (this->appliedShape != this->currentShape) {
            this->cursor = glfwCreateStandardCursor(mapCursorShape(this->currentShape));
            glfwSetCursor(this->window, this->cursor);    
            this->appliedShape = this->currentShape;
        }
    }

    void GLCursor::set(CursorShape shape) {
        this->currentShape = shape;
        this->platform->requestNextFrame([this] () {
            this->updateCursor();
        });
    }

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

    GLFontManager::GLFontManager() {
        this->skFontManager = sk_make_sp<sktextlayout::TypefaceFontProvider>();
    }

    sk_sp<SkFontMgr> GLFontManager::getSkFontManager() {
        return this->skFontManager;
    }

    void GLFontManager::registerFontFromSkData(sk_sp<SkData> data) {
        this->skFontManager->registerTypeface(SkTypeface::MakeFromData(data));
    }

    void GLFontManager::registerFontFromPath(std::string path) {
        this->registerFontFromSkData(SkData::MakeFromFileName(path.c_str()));
    }
}

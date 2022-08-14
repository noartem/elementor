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

#include "GLApplication.h"

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

#define GL_RGBA8 0x8058

namespace elementor {
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

    unsigned int mapCursorShapeToInt(CursorShape shape) {
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
            default:
                return GLFW_ARROW_CURSOR;
        }
    }

    Size getWindowSize(GLFWwindow *window) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        return {(float) width, (float) height};
    }

    Position getWindowPosition(GLFWwindow *window) {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        return {(float) x, (float) y};
    }

    Rect getWindowRect(GLFWwindow *window) {
        return {getWindowSize(window), getWindowPosition(window)};
    }

    Size getMonitorSize(GLFWmonitor *monitor) {
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        return {(float) mode->width, (float) mode->height};
    }

    Size getMonitorPhysicalSize(GLFWmonitor *monitor) {
        int width, height;
        glfwGetMonitorPhysicalSize(monitor, &width, &height);
        return {(float) width, (float) height};
    }

    Position getMonitorPosition(GLFWmonitor *monitor) {
        int x, y;
        glfwGetMonitorPos(monitor, &x, &y);
        return {(float) x, (float) y};
    }

    Rect getMonitorRect(GLFWmonitor *monitor) {
        return {getMonitorSize(monitor), getMonitorPosition(monitor)};
    }

    GLFWmonitor* getWindowMonitor(GLFWwindow* window) {
        Rect windowRect = getWindowRect(window);

        int monitorsSize = 0;
        GLFWmonitor** monitors = glfwGetMonitors(&monitorsSize);

        GLFWmonitor* closestMonitor;
        int maxOverlapArea = 0;

        for (unsigned int i = 0; i < monitorsSize; i++) {
            GLFWmonitor *monitor = monitors[i];
            Rect monitorRect = getMonitorRect(monitor);

            float overlapWidth = windowRect.size.width - std::max((monitorRect.position.x - windowRect.position.x), ZERO) - std::max((windowRect.position.x + windowRect.size.width) - (monitorRect.position.x + monitorRect.size.width), ZERO);
            float overlapHeight = windowRect.size.height - std::max((monitorRect.position.y - windowRect.position.y), ZERO) - std::max((windowRect.position.y + windowRect.size.height) - (monitorRect.position.y + monitorRect.size.height), ZERO);
            float overlapArea = overlapWidth * overlapHeight;
            if (overlapArea > maxOverlapArea) {
                closestMonitor = monitor;
                maxOverlapArea = overlapArea;
            }
        }

        return closestMonitor;
    }

    float calcMonitorPixelScale(Size pixelSize, Size physicalSize) {
        return (pixelSize.width / physicalSize.width) / DefaultMonitorScale;
    }

    GLWindow *getGLFWwindowGLWindow(GLFWwindow *window) {
        return static_cast<GLWindow *>(glfwGetWindowUserPointer(window));
    }

    GLApplication::GLApplication() {
        this->clipboard = new GLClipboard();
        this->perfomance = new GLPerfomance();
        this->fontManager = new GLFontManager();
        this->applicationContext = new GLApplicationContext(this);

        glfwInit();

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
    }

    void GLApplication::run() {
        for (GLWindow *window : this->windows) {
            window->refresh();
        }

        for (;;) {
            this->applyRnfQueue();

            for (GLWindow *window : this->windows) {
                if (window->shouldClose()) {
                    window->close();
                    // TODO: remove window
                } else {
                    window->draw();
                }
            }

            this->perfomance->incrementFramesCount();

            // TODO: if new windows size equals 0 *break*

            glfwWaitEvents();
        }
        

        glfwTerminate();
    }

    GLClipboard *GLApplication::getClipboard() {
        return this->clipboard;
    }

    GLFontManager *GLApplication::getFontManager() {
        return this->fontManager;
    }

    GLPerfomance *GLApplication::getPerfomance() {
        return this->perfomance;
    }

    sk_sp<SkFontMgr> GLApplication::getSkFontManager() {
        return this->fontManager->getSkFontManager();
    }

    void GLApplication::requestNextFrame(std::function<void ()> callback) {
        glfwPostEmptyEvent();
        this->rnfNextQueue.push_back(callback);
    }

    void GLApplication::applyRnfQueue() {
        if (this->rnfCurrentQueue.empty() && this->rnfNextQueue.empty() > 0) {
            return;
        }

        for (std::function<void ()> callback : this->rnfCurrentQueue) {
            callback();
        }

        this->rnfCurrentQueue = this->rnfNextQueue;
        this->rnfNextQueue = {};
    }

    GLWindow *GLApplication::makeWindow() {
        GLWindow *window = new GLWindow(this->applicationContext);
        this->windows.push_back(window);
        return window;
    }

    GLMonitor::GLMonitor(GLFWmonitor *monitor) {
        this->size = getMonitorSize(monitor);
        this->physicalSize = getMonitorPhysicalSize(monitor);
        this->pixelScale = calcMonitorPixelScale(this->size, this->physicalSize);
    }

    Size GLMonitor::getSize() {
        return this->size;
    }

    Size GLMonitor::getPhysicalSize() {
        return this->physicalSize;
    }

    float GLMonitor::getPixelScale() {
        return this->pixelScale;
    }

    void GLMonitor::setPixelScale(float scale) {
        this->pixelScale = scale;
    }

    GLWindow::GLWindow(ApplicationContext *applicationContext) {
        this->application = new Application();
        this->applicationContext = applicationContext;
        this->glWindow = glfwCreateWindow(100, 100, "Elementor", nullptr, nullptr);
        this->cursor = new GLCursor(this->glWindow, this->applicationContext);

        glfwMakeContextCurrent(this->glWindow);
        glfwSwapInterval(1);
        glfwSetWindowUserPointer(this->glWindow, this);

        this->skContext = GrDirectContext::MakeGL(GrGLMakeNativeInterface()).release();

        glfwSetWindowRefreshCallback(glWindow, [] (GLFWwindow* glWindow) {
            GLWindow *window = getGLFWwindowGLWindow(glWindow);
            window->refresh();
        });

        this->updateMonitor();
        glfwSetWindowPosCallback(glWindow, [] (GLFWwindow* glWindow, int xpos, int ypos) {
            GLWindow *window = getGLFWwindowGLWindow(glWindow);
            window->updateMonitor();
        });

        glfwSetKeyCallback(glWindow, [] (GLFWwindow *glWindow, int key, int scancode, int action, int mods) {
            GLWindow *window = getGLFWwindowGLWindow(glWindow);
            window->onKeyboard(key, scancode, action, mods);
        });

        glfwSetCharCallback(glWindow, [] (GLFWwindow *glWindow, unsigned int codepoint) {
            GLWindow *window = getGLFWwindowGLWindow(glWindow);
            window->onChar(codepoint);
        });

        glfwSetMouseButtonCallback(glWindow, [] (GLFWwindow* glWindow, int button, int action, int mods) {
            GLWindow *window = getGLFWwindowGLWindow(glWindow);
            window->onMouseButton(button, action, mods);
        });

        glfwSetCursorPosCallback(glWindow, [] (GLFWwindow* glWindow, double x, double y) {
            GLWindow *window = getGLFWwindowGLWindow(glWindow);
            window->onMouseMove(x, y);
        });

        glfwSetScrollCallback(glWindow, [] (GLFWwindow* glWindow, double xOffset, double yOffset) {
            GLWindow *window = getGLFWwindowGLWindow(glWindow);
            window->onScroll(xOffset, yOffset);
        });
    }

    void GLWindow::refresh() {
        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0;
        framebufferInfo.fFormat = GL_RGBA8;

        Size size = this->getSize();

        GrBackendRenderTarget backendRenderTarget(size.width, size.height, 0, 0, framebufferInfo);
        this->skSurface = SkSurface::MakeFromBackendRenderTarget(this->skContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin,
                                                                 kRGBA_8888_SkColorType, SkColorSpace::MakeSRGB(), nullptr)
                                                                 .release();
        this->skCanvas = this->skSurface->getCanvas();
    }

    void GLWindow::draw() {
        glfwMakeContextCurrent(this->glWindow);
        this->skCanvas->clear(SK_ColorBLACK);
        this->application->draw(this->applicationContext, this, this->skCanvas);
        this->skContext->flush();
        glfwSwapBuffers(this->glWindow);
    }

    void GLWindow::updateMonitor() {
        GLFWmonitor *newGlMonitor = getWindowMonitor(this->glWindow);
        if (newGlMonitor != this->glMonitor) {
            this->glMonitor = newGlMonitor;
            this->monitor = new GLMonitor(newGlMonitor);   
        }
    }

    Element *GLWindow::getRoot() {
        return this->root;
    }

    void GLWindow::setRoot(Element *root) {
        this->root = root;
    }

    void GLWindow::setTitle(std::string title) {
        this->title = title;
        glfwSetWindowTitle(this->glWindow, title.c_str());
    }

    std::string GLWindow::getTitle() {
        return this->title;
    }

    Size GLWindow::getSize() {
        return getWindowSize(this->glWindow);
    }

    void GLWindow::setSize(Size size) {
        glfwSetWindowSize(this->glWindow, std::ceil(size.width), std::ceil(size.height));
    }

    std::optional<Size> GLWindow::getMinSize() {
        return this->minSize;    
    }

    std::optional<Size> GLWindow::getMaxSize() {
        return this->maxSize;
    }

    void GLWindow::updateWindowSizeLimits() {
        if (this->minSize && this->maxSize) {
            glfwSetWindowSizeLimits(this->glWindow, this->minSize->width, this->minSize->height, this->maxSize->width, this->maxSize->height);
        } else if (this->minSize && !this->maxSize) {
            glfwSetWindowSizeLimits(this->glWindow, this->minSize->width, this->minSize->height, GLFW_DONT_CARE, GLFW_DONT_CARE);
        } else if (!this->minSize && this->maxSize) {
            glfwSetWindowSizeLimits(this->glWindow, GLFW_DONT_CARE, GLFW_DONT_CARE, this->maxSize->width, this->maxSize->height);
        } else {
            glfwSetWindowSizeLimits(this->glWindow, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
        }
    }

    void GLWindow::setMinSize(Size size) {
        this->minSize = size;
        this->updateWindowSizeLimits();
    }

    void GLWindow::setMaxSize(Size size) {
        this->maxSize = size;
        this->updateWindowSizeLimits();
    }

    Position GLWindow::getPosition() {
        return getWindowPosition(this->glWindow);
    }

    void GLWindow::setPosition(Position position) {
        glfwSetWindowPos(this->glWindow, std::ceil(position.x), std::ceil(position.y));
    }

    bool GLWindow::shouldClose() {
        return glfwWindowShouldClose(this->glWindow);        
    }

    void GLWindow::close() {
        glfwDestroyWindow(this->glWindow);
    }

    Cursor *GLWindow::getCursor() {
        return this->cursor;
    }

    Monitor *GLWindow::getMonitor() {
        return this->monitor;
    }

    void GLWindow::onMouseButton(int button, int action, int mods) {
        EventMouseButton *event = new EventMouseButton();
        event->button = mapIntToMouseButton(button);
        event->action = mapIntToKeyAction(action);
        event->mod = mapIntToKeyMod(mods);

        this->application->dispatchEvent(event);
    }

    void GLWindow::onKeyboard(int key, int scancode, int action, int mods) {
        EventKeyboard *event = new EventKeyboard();
        event->key = mapIntToKeyboardKey(key);
        event->scancode = scancode;
        event->action = mapIntToKeyAction(action);
        event->mod = mapIntToKeyMod(mods);

        this->application->dispatchEvent(event);
    }

    void GLWindow::onChar(unsigned int codepoint) {
        EventChar *event = new EventChar();
        event->value = codepoint;

        this->application->dispatchEvent(event);
    }

    void GLWindow::onMouseMove(double x, double y) {
        EventMouseMove *event = new EventMouseMove();
        event->x = x;
        event->y = y;

        this->application->dispatchEvent(event);
    }

    void GLWindow::onScroll(double xOffset, double yOffset) {
        EventScroll *event = new EventScroll();
        event->xOffset = xOffset;
        event->yOffset = yOffset;

        this->application->dispatchEvent(event);
    }

    GLApplicationContext::GLApplicationContext(GLApplication *application) {
        this->application = application;
    }

    Clipboard *GLApplicationContext::getClipboard() {
        return this->application->getClipboard();
    }

    Perfomance *GLApplicationContext::getPerfomance() {
        return this->application->getPerfomance();
    }

    sk_sp<SkFontMgr> GLApplicationContext::getSkFontManager() {
        return this->application->getSkFontManager();
    }

    void GLApplicationContext::requestNextFrame(std::function<void ()> callback) {
        this->application->requestNextFrame(callback);
    }

    void GLClipboard::set(std::string value) {
        glfwSetClipboardString(nullptr, value.c_str());
    }

    std::string GLClipboard::get() {
        return glfwGetClipboardString(nullptr);
    }

    GLCursor::GLCursor(GLFWwindow *window, ApplicationContext *ctx) {
        this->window = window;
        this->ctx = ctx;
    }

    void GLCursor::updateCursor() {
        if (this->appliedShape != this->currentShape) {
            this->cursor = glfwCreateStandardCursor(mapCursorShapeToInt(this->currentShape));
            glfwSetCursor(this->window, this->cursor);    
            this->appliedShape = this->currentShape;
        }
    }

    void GLCursor::set(CursorShape shape) {
        this->currentShape = shape;
        this->ctx->requestNextFrame([this] () {
            this->updateCursor();
        });
    }

    CursorShape GLCursor::get() {
        return this->currentShape;
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


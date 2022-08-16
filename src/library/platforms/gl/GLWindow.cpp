//
// Created by noartem on 14.04.2022.
//

#include "GLWindow.h"
#include "utility.h"

#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define GL_RGBA8 0x8058

namespace elementor {
    GLWindow *getGLFWwindowGLWindow(GLFWwindow *window) {
        return static_cast<GLWindow *>(glfwGetWindowUserPointer(window));
    }

    GLWindow::GLWindow(ApplicationContext *applicationContext) {
        this->application = new Application();
        this->applicationContext = applicationContext;
        this->glWindow = glfwCreateWindow(1, 1, "Elementor", nullptr, nullptr);
        this->cursor = new GLCursor(this->glWindow, this->applicationContext);

        glfwMakeContextCurrent(this->glWindow);
        glfwSwapInterval(0); // TODO: Check if it is a problem
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

        glfwSetWindowCloseCallback(glWindow, [] (GLFWwindow* glWindow) {
            GLWindow *window = getGLFWwindowGLWindow(glWindow);
            window->close();
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
        Size size = this->getSize();

        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0;
        framebufferInfo.fFormat = GL_RGBA8;

        glfwMakeContextCurrent(this->glWindow);
        GrBackendRenderTarget backendRenderTarget(size.width, size.height, 0, 0, framebufferInfo);
        this->skSurface = SkSurface::MakeFromBackendRenderTarget(this->skContext, backendRenderTarget,
                                                                 kBottomLeft_GrSurfaceOrigin, kRGBA_8888_SkColorType,
                                                                 SkColorSpace::MakeSRGB(), nullptr);
        this->skCanvas = this->skSurface->getCanvas();
    }

    void GLWindow::draw() {
        this->refresh();

        this->skCanvas->clear(SK_ColorBLACK);
        this->application->draw(this->applicationContext, this, this->skCanvas);

        glfwMakeContextCurrent(this->glWindow);
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

    void GLWindow::close() {
        glfwDestroyWindow(this->glWindow);

        if (this->callbackClose) {
            this->callbackClose();
        }
    }

    void GLWindow::onClose(std::function<void ()> callback) {
        this->callbackClose = callback;
    }

    Cursor *GLWindow::getCursor() {
        return this->cursor;
    }

    Monitor *GLWindow::getMonitor() {
        return this->monitor;
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

    void GLWindow::onMouseButton(int button, int action, int mods) {
        EventMouseButton *event = new EventMouseButton();
        event->button = mapIntToMouseButton(button);
        event->action = mapIntToKeyAction(action);
        event->mod = mapIntToKeyMod(mods);

        this->application->dispatchEvent(event);
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
}


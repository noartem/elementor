//
// Created by noartem on 14.04.2022.
//

#include "GLFW/glfw3.h"

#define SK_GL

#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"

#include "Platform.h"

#include <stdio.h>
#include <stdlib.h>

#define GL_RGBA8 0x8058

namespace elementor {
    Size Platform::getWindowSize() {
        int width, height;
        glfwGetFramebufferSize(this->window, &width, &height);
        return {(float) width, (float) height};
    }

    Size Platform::getMonitorPhysicalSize() {
        int width, height;
        glfwGetMonitorPhysicalSize(this->monitor, &width, &height);
        return {(float) width, (float) height};
    }

    Size Platform::getMonitorSize() {
        const GLFWvidmode* mode = glfwGetVideoMode(this->monitor);
        return {(float) mode->width, (float) mode->height};
    }

    float Platform::calcMonitorPixelScale(Size monitorPhysicalSize) {
        Size monitorSize = this->getMonitorSize();
        return (monitorSize.width / monitorPhysicalSize.width) / DefaultMonitorScale;
    }

    void Platform::refresh() {
        ApplicationContext applicationContext;
        applicationContext.windowSize = this->getWindowSize();
        applicationContext.monitorPhysicalSize = this->getMonitorPhysicalSize();
        applicationContext.monitorPixelScale = this->calcMonitorPixelScale(applicationContext.monitorPhysicalSize);
        applicationContext.root = NULL;
        this->applicationContext = applicationContext;

        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0;
        framebufferInfo.fFormat = GL_RGBA8;

        if (this->skiaSurface) {
            delete this->skiaSurface;
        }

        // create skia canvas
        GrBackendRenderTarget backendRenderTarget(applicationContext.windowSize.width, applicationContext.windowSize.height, 0, 0, framebufferInfo);
        this->skiaSurface = SkSurface::MakeFromBackendRenderTarget(this->skiaContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, kRGBA_8888_SkColorType, SkColorSpace::MakeSRGB(), nullptr).release();
        this->skiaCanvas = this->skiaSurface->getCanvas();
    }

    void Platform::draw() {
        this->skiaCanvas->clear(SK_ColorBLACK);
        this->application->draw(&this->applicationContext, this->skiaCanvas);

        this->skiaContext->flush();
        glfwSwapBuffers(this->window);
    }

    void Platform::onMouseButton(int button, int action, int mods) {
        EventMouseButton *event = new EventMouseButton();
        event->button = static_cast<MouseButton>(button);
        event->action = static_cast<Action>(action);
        event->mod = static_cast<Mod>(mods);

        this->application->dispatchEvent(event);
    }

    void Platform::onKeyboard(int key, int scancode, int action, int mods) {
        EventKeyboard *event = new EventKeyboard();
        event->key = static_cast<KeyboardKey>(key);
        event->scancode = scancode;
        event->action = static_cast<Action>(action);
        event->mod = static_cast<Mod>(mods);

        this->application->dispatchEvent(event);
    }

    void Platform::onMouseMove(double x, double y) {
        EventMouseMove *event = new EventMouseMove();
        event->x = x;
        event->y = y;

        this->application->dispatchEvent(event);
    }

    void Platform::onScroll(double xOffset, double yOffset) {
        EventScroll *event = new EventScroll();
        event->xOffset = xOffset;
        event->yOffset = yOffset;

        this->application->dispatchEvent(event);
    }

    Platform *getWindowPlatform(GLFWwindow *window) {
        return static_cast<Platform *>(glfwGetWindowUserPointer(window));
    }

    int Platform::run() {
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
            Platform *platform = getWindowPlatform(window);
            platform->onKeyboard(key, scancode, action, mods);
        });

        glfwSetMouseButtonCallback(window, [] (GLFWwindow* window, int button, int action, int mods) {
            Platform *platform = getWindowPlatform(window);
            platform->onMouseButton(button, action, mods);
        });

        glfwSetCursorPosCallback(window, [] (GLFWwindow* window, double x, double y) {
            Platform *platform = getWindowPlatform(window);
            platform->onMouseMove(x, y);
        });

        glfwSetScrollCallback(window, [] (GLFWwindow* window, double xOffset, double yOffset) {
            Platform *platform = getWindowPlatform(window);
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
            Platform *platform = getWindowPlatform(window);
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
}

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

#define GL_FRAMEBUFFER_SRGB 0x8DB9
#define GL_SRGB8_ALPHA8 0x8C43

namespace elementor {
    void callbackEventMouseButton(GLFWwindow* window, int button, int action, int mods) {
        EventMouseButton *event = new EventMouseButton();
        event->button = static_cast<MouseButton>(button);
        event->action = static_cast<MouseAction>(action);
        event->mod = static_cast<MouseMod>(mods);

        Platform *platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
        platform->application->dispatchEvent(event);
    }

    void callbackEventMouseMove(GLFWwindow* window, double x, double y) {
        EventMouseMove *event = new EventMouseMove();
        event->x = x;
        event->y = y;

        Platform *platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
        platform->application->dispatchEvent(event);
    }

    int Platform::run() {
        // init glfw
        GLFWwindow *window;
        glfwSetErrorCallback([] (int error, const char *description) {
            fputs(description, stderr);
        });
        if (!glfwInit()) {
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_STENCIL_BITS, 0);
        glfwWindowHint(GLFW_ALPHA_BITS, 0);
        glfwWindowHint(GLFW_DEPTH_BITS, 0);

        window = glfwCreateWindow(this->size.width, this->size.height, this->title.c_str(), NULL, NULL);
        if (!window) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        if (this->minSize && this->maxSize) {
            glfwSetWindowSizeLimits(window, this->minSize->width, this->minSize->height, this->maxSize->width, this->maxSize->height);
        } else if (this->minSize && !this->maxSize) {
            glfwSetWindowSizeLimits(window, this->minSize->width, this->minSize->height, GLFW_DONT_CARE, GLFW_DONT_CARE);
        } else if (!this->minSize && this->maxSize) {
            glfwSetWindowSizeLimits(window, GLFW_DONT_CARE, GLFW_DONT_CARE, this->maxSize->width, this->maxSize->height);
        }

        glfwMakeContextCurrent(window);
        // glEnable(GL_FRAMEBUFFER_SRGB);

        glfwSwapInterval(1);

        glfwSetWindowUserPointer(window, this);

        glfwSetKeyCallback(window, [] (GLFWwindow *window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
        });

        glfwSetMouseButtonCallback(window, [] (GLFWwindow* window, int button, int action, int mods) {
            callbackEventMouseButton(window, button, action, mods);
        });

        glfwSetCursorPosCallback(window, [] (GLFWwindow* window, double x, double y) {
            callbackEventMouseMove(window, x, y);
        });

        GLFWmonitor* monitor = glfwGetWindowMonitor(window);
        if (monitor == NULL) {
            monitor = glfwGetPrimaryMonitor();
        }

        int physicalWidth, physicalHeight;
        glfwGetMonitorPhysicalSize(monitor, &physicalWidth, &physicalHeight);
        Size monitorPhysicalSize = {physicalWidth, physicalHeight};

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        Size monitorSize = {mode->width, mode->height};

        float monitorPixelScale = ((float)monitorSize.width / (float)monitorPhysicalSize.width) / DefaultMonitorScale;

        // init skia
        auto interface = GrGLMakeNativeInterface();
        GrDirectContext *context = GrDirectContext::MakeGL(interface).release();

        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0;
        framebufferInfo.fFormat = GL_SRGB8_ALPHA8;

        SkColorType colorType = kRGBA_8888_SkColorType;

        while (!glfwWindowShouldClose(window)) {
            glfwWaitEvents();

            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            Size windowSize = {width, height};

            // create skia canvas
            GrBackendRenderTarget backendRenderTarget(width, height, 0, 0, framebufferInfo);
            SkSurface *surface = SkSurface::MakeFromBackendRenderTarget(context, backendRenderTarget,
                                                                        kBottomLeft_GrSurfaceOrigin, colorType,
                                                                        SkColorSpace::MakeSRGB(), nullptr).release();
            SkCanvas *canvas = surface->getCanvas();
            canvas->clear(SK_ColorBLACK);

            // draw application
            ApplicationContext applicationContext;
            applicationContext.windowSize = windowSize;
            applicationContext.monitorPhysicalSize = monitorPhysicalSize;
            applicationContext.monitorPixelScale = monitorPixelScale;

            this->application->draw(canvas, applicationContext);

            context->flush();
            glfwSwapBuffers(window);

            delete surface;
        }

        // cleanup skia
        delete context;

        // cleanup glfw
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
}

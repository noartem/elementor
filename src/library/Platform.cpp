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

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

namespace elementor {
    int Platform::run() {
        // init glfw
        GLFWwindow* window;
        glfwSetErrorCallback(error_callback);
        if (!glfwInit()) {
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
        glfwWindowHint(GLFW_STENCIL_BITS, 0);
        glfwWindowHint(GLFW_ALPHA_BITS, 0);
        glfwWindowHint(GLFW_DEPTH_BITS, 0);

        window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
        if (!window) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);
        glEnable(GL_FRAMEBUFFER_SRGB);

        glfwSwapInterval(1);
        glfwSetKeyCallback(window, key_callback);

        // init skia
        auto interface = GrGLMakeNativeInterface();
        GrDirectContext* context = GrDirectContext::MakeGL(interface).release();

        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0;
        framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
        framebufferInfo.fFormat = GL_RGBA8;

        SkColorType colorType = kRGBA_8888_SkColorType;

        while (!glfwWindowShouldClose(window)) {
            glfwWaitEvents();
            glClear(GL_COLOR_BUFFER_BIT);

            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            RenderSize windowSize = {width, height};

            // create skia canvas
            GrBackendRenderTarget backendRenderTarget(width, height, 0, 0, framebufferInfo);
            SkSurface* surface = SkSurface::MakeFromBackendRenderTarget(context, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(), nullptr).release();
            SkCanvas* canvas = surface->getCanvas();

            // draw with skia
            canvas->clear(SK_ColorBLACK);
            this->draw(canvas, windowSize);

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

    void Platform::draw(SkCanvas *canvas, RenderSize size) {
        this->application->draw(canvas, size);
    }
}

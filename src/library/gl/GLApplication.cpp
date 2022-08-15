//
// Created by noartem on 14.04.2022.
//

#include "GLApplication.h"
#include "GLApplicationContext.h"

#include "GLFW/glfw3.h"

#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"

#define SK_GL

#define GL_RGBA8 0x8058

namespace elementor {
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
}


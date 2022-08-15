//
// Created by noartem on 14.04.2022.
//

#include "GLPlatform.h"
#include "GLApplicationContext.h"

#include "GLFW/glfw3.h"

#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"

#define GL_RGBA8 0x8058

namespace elementor {
    GLPlatform::GLPlatform() {
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

    void GLPlatform::run() {
        for (;;) {
            this->applyRnfQueue();

            for (GLWindow *window : this->windows) {
                if (window->shouldClose()) {
                    window->close();
                } else {
                    window->draw();
                }
            }

            this->perfomance->incrementFramesCount();

            if (this->windows.size() == 0) {
                break;
            }

            glfwWaitEvents();
        }
        

        glfwTerminate();
    }

    GLClipboard *GLPlatform::getClipboard() {
        return this->clipboard;
    }

    GLFontManager *GLPlatform::getFontManager() {
        return this->fontManager;
    }

    GLPerfomance *GLPlatform::getPerfomance() {
        return this->perfomance;
    }

    sk_sp<SkFontMgr> GLPlatform::getSkFontManager() {
        return this->fontManager->getSkFontManager();
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

    GLWindow *GLPlatform::makeWindow() {
        GLWindow *window = new GLWindow(this->applicationContext);
        this->addWindow(window);
        return window;
    }

    void GLPlatform::addWindow(GLWindow *window) {
        window->onClose([this, window] () {
            this->removeWindow(window);
        });
        this->windows.push_back(window);
    }

    void GLPlatform::removeWindow(unsigned int index) {
        if (index < this->windows.size()) {
            this->windows.erase(this->windows.begin() + index);
        }
    }

    void GLPlatform::removeWindow(GLWindow *window) {
        for (unsigned int i = 0; i < this->windows.size(); ++i) {
            if (this->windows[i] == window) {
                this->removeWindow(i);
                return;
            }
        }
    }
}


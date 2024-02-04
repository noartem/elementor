//
// Created by noartem on 14.04.2022.
//

#include "GLPlatform.h"

#include "GLFW/glfw3.h"

#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"

#define GL_RGBA8 0x8058

namespace elementor::platforms::gl {
	void onGLFWError(int error, const char* description) {
		fputs(description, stderr);
	}

	GLPlatform::GLPlatform() {
		glfwInit();
		glfwSetErrorCallback(onGLFWError);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_STENCIL_BITS, 0);
		glfwWindowHint(GLFW_ALPHA_BITS, 0);
		glfwWindowHint(GLFW_DEPTH_BITS, 0);

		this->eventLoop = std::make_shared<GLEventLoop>();

		this->clipboard = std::make_shared<GLClipboard>();
		this->perfomance = std::make_shared<GLPerfomance>();
		this->fontManager = std::make_shared<GLFontManager>();
	}

	void GLPlatform::run() {
		eventLoop->setCallback([this]() {
			applyRnfQueue();

			for (const std::shared_ptr<GLWindow>& window: windows) {
				window->draw();
			}

			if (windows.empty()) {
				return true;
			}

			perfomance->incrementFramesCount();

			return false;
		});

		eventLoop->start();

		glfwTerminate();
	}

	void GLPlatform::requestNextFrame(const std::function<void()>& callback) {
		rnfNextQueue.push_back(callback);
		eventLoop->pend();
	}

	void GLPlatform::requestNextFrame() {
		eventLoop->pend();
	}

	void GLPlatform::applyRnfQueue() {
		if (this->rnfCurrentQueue.empty() && this->rnfNextQueue.empty()) {
			return;
		}

		for (const std::function<void()>& callback: this->rnfCurrentQueue) {
			callback();
		}

		this->rnfCurrentQueue = this->rnfNextQueue;
		this->rnfNextQueue = {};
	}

	void GLPlatform::addWindow(const std::shared_ptr<GLWindow>& window) {
		window->onClose([this, window]() { this->removeWindow(window); });
		this->windows.push_back(window);
	}

	void GLPlatform::removeWindow(unsigned int index) {
		if (index < this->windows.size()) {
			this->windows.erase(this->windows.begin() + index);
		}
	}

	void GLPlatform::removeWindow(const std::shared_ptr<GLWindow>& window) {
		for (unsigned int i = 0; i < this->windows.size(); ++i) {
			if (this->windows[i] == window) {
				this->removeWindow(i);
				return;
			}
		}
	}
}


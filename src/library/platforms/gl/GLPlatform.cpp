//
// Created by noartem on 14.04.2022.
//

#include "GLPlatform.h"

#include "GLFW/glfw3.h"

#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"

namespace elementor::platforms::gl {
	void onGLFWError([[maybe_unused]] int error, const char* description) {
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

		eventLoop = std::make_shared<GLEventLoop>();

		clipboard = std::make_shared<GLClipboard>();
		perfomance = std::make_shared<GLPerfomance>();
		fontManager = std::make_shared<GLFontManager>();
	}

	void GLPlatform::run() {
		for (;;) {
			glfwWaitEvents();

			applyRnfQueue();

			for (const std::shared_ptr<GLWindow>& window: windows) {
				window->tick();
			}

			if (windows.empty()) {
				break;
			}

			perfomance->incrementFramesCount();
		}

		glfwTerminate();
	}

	void GLPlatform::requestNextFrame(const std::function<void()>& callback) {
		rnfQueue.push_back(callback);
		eventLoop->pend();
	}

	void GLPlatform::requestNextFrame() {
		eventLoop->pend();
	}

	void GLPlatform::applyRnfQueue() {
		if (rnfQueue.empty()) {
			return;
		}

		auto rnfCurrentQueue = rnfQueue;
		rnfQueue = {};
		for (const std::function<void()>& callback: rnfCurrentQueue) {
			callback();
		}
	}

	void GLPlatform::addWindow(const std::shared_ptr<GLWindow>& window) {
		window->onClose([this, window]() { removeWindow(window); });
		windows.push_back(window);
	}

	void GLPlatform::removeWindow(unsigned int index) {
		if (index < windows.size()) {
			windows.erase(windows.begin() + index);
		}
	}

	void GLPlatform::removeWindow(const std::shared_ptr<GLWindow>& window) {
		for (unsigned int i = 0; i < windows.size(); ++i) {
			if (windows[i] == window) {
				removeWindow(i);
				return;
			}
		}
	}
}


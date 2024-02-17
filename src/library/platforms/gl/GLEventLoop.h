//
// Created by noartem on 13.01.2024.
//

#ifndef ELEMENTOR_GL_EVENT_LOOP_H
#define ELEMENTOR_GL_EVENT_LOOP_H

#include <chrono>

#include "GLFW/glfw3.h"

#include "elementor.h"

namespace elementor::platforms::gl {
	class GLEventLoop {
	public:
		explicit GLEventLoop(const std::function<bool()>& callback)
			: callback(callback) {
		}

		void run() {
			running = true;

			for (;;) {
				D(
					const char* glfwErrorDescription;
					int glfwErrorCode = glfwGetError(&glfwErrorDescription);
					if (glfwErrorCode != 0 || glfwErrorDescription) {
						D_LOG("GLFW error: " << glfwErrorDescription << " (" << glfwErrorCode << ")" << std::endl);
					}
				);

				glfwWaitEvents();

				D(
					glfwErrorCode = glfwGetError(&glfwErrorDescription);
					if (glfwErrorCode != 0 || glfwErrorDescription) {
						D_LOG("GLFW error: " << glfwErrorDescription << " (" << glfwErrorCode << ")" << std::endl);
					}
				);

				tryCallCallback();
				if (shouldBreak) {
					break;
				}
			}

			running = false;
		}

		void pend() {
			glfwPostEmptyEvent();
			tryCallCallback();
		}

	private:
		bool running = false;

		std::function<bool()> callback;

		std::chrono::steady_clock::time_point lastCallbackCall = std::chrono::steady_clock::now();
		bool shouldBreak = false;

		void tryCallCallback() {
			if (!running) {
				return;
			}

			auto now = std::chrono::steady_clock::now();

			if (now - lastCallbackCall > std::chrono::milliseconds(1)) {
				lastCallbackCall = now;
				shouldBreak |= callback();
			}
		}
	};
}

#endif //ELEMENTOR_GL_EVENT_LOOP_H

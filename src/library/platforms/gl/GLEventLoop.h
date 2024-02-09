//
// Created by noartem on 13.01.2024.
//

#ifndef ELEMENTOR_GL_EVENT_LOOP_H
#define ELEMENTOR_GL_EVENT_LOOP_H

#include <chrono>

#include "GLFW/glfw3.h"

#include "elementor.h"
#include "../../debug.h"

namespace elementor::platforms::gl {
	class GLEventLoop {
	public:
		explicit GLEventLoop(const std::function<bool()>& callback) : callback(callback) {}

		void run() {
			for (;;) {
				glfwWaitEvents();

				tryCallCallback();
				if (shouldBreak) {
					break;
				}
			}
		}

		void pend() {
			E_LOG("pend");
			glfwPostEmptyEvent();
			tryCallCallback();
		}

	private:
		std::function<bool()> callback;

		std::chrono::steady_clock::time_point lastCallbackCall = std::chrono::steady_clock::now();
		bool shouldBreak = false;

		void tryCallCallback() {
			auto now = std::chrono::steady_clock::now();

			if (now - lastCallbackCall > std::chrono::milliseconds(1)) {
				lastCallbackCall = now;
				shouldBreak |= callback();
			}
		}
	};
}

#endif //ELEMENTOR_GL_EVENT_LOOP_H

//
// Created by admin on 13.01.2024.
//

#ifndef ELEMENTOR_GL_EVENT_LOOP_H
#define ELEMENTOR_GL_EVENT_LOOP_H

#include <chrono>

#include "GLFW/glfw3.h"

#include "elementor.h"

namespace elementor::platforms::gl {
	class GLEventLoop {
	public:
		explicit GLEventLoop() = default;

		void start() {
			for (;;) {
				glfwWaitEvents();

				if (callback) {
					auto shouldBreak = callback();
					if (shouldBreak) {
						break;
					}
				}
			}
		}

		void pend() {
			glfwPostEmptyEvent();
		}

		void setCallback(const std::function<bool()>& newCallback) {
			callback = newCallback;
		}

	private:
		std::function<bool()> callback = nullptr;
	};
}

#endif //ELEMENTOR_GL_EVENT_LOOP_H

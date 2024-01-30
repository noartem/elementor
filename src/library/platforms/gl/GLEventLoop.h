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
		explicit GLEventLoop() {
		}

		void start() {
			for (;;) {
				glfwWaitEvents();

				if (pendingBreak) {
					break;
				}

				auto shouldBreak = callCallback();
				if (shouldBreak) {
					break;
				}
			}
		}

		void stop() {
			pendingBreak = true;
		}

		void pend() {
			glfwPostEmptyEvent();

			if (!canCall()) {
				return;
			}

			auto shouldBreak = callCallback();
			if (shouldBreak) {
				pendingBreak = true;
			}
		}

		void setCallback(const std::function<bool()>& newCallback) {
			callback = newCallback;
		}

	private:
		std::function<bool()> callback = nullptr;
		uint32_t interval = 1000 / 60;
		bool pendingBreak = false;
		std::chrono::steady_clock::time_point lastCallTime;

		bool callCallback() {
			if (!callback) {
				return false;
			}

			lastCallTime = std::chrono::steady_clock::now();

			return callback();
		}

		bool canCall() {
			auto currentTime = std::chrono::steady_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(
					currentTime - lastCallTime).count();
			return elapsedTime >= interval;
		}
	};
}

#endif //ELEMENTOR_GL_EVENT_LOOP_H

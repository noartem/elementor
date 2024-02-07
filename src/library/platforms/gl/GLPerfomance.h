//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_PERFOMANCE_H
#define ELEMENTOR_GL_PERFOMANCE_H

#include "elementor.h"

#include "GLFW/glfw3.h"

namespace elementor::platforms::gl {
	class GLPerfomance : public Perfomance {
	public:
		double getFPS() override {
			return lastFPS;
		}

		void incrementFramesCount() {
			framesCount++;

			double now = glfwGetTime();
			if ((now - framesLastTime) >= 1) {
				lastFPS = framesCount;
				framesLastTime = now;
				framesCount = 0;
			}
		}

	private:
		double framesLastTime;
		double framesCount;
		double lastFPS;
	};
};

#endif //ELEMENTOR_GL_PERFOMANCE_H

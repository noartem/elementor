//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_DISPLAY_H
#define ELEMENTOR_GL_DISPLAY_H

#include "elementor.h"

#include "GLFW/glfw3.h"

#include "utility.h"

namespace elementor::platforms::gl {
	class GLDisplay : public Display {
	public:
		GLDisplay(GLFWmonitor* glMonitor) {
			size = getMonitorSize(glMonitor);
			physicalSize = getMonitorPhysicalSize(glMonitor);
		}

		Size getSize() override {
			return size;
		}

		Size getPhysicalSize() override {
			return physicalSize;
		}

	private:
		Size size;
		Size physicalSize;
	};
};

#endif //ELEMENTOR_GL_DISPLAY_H

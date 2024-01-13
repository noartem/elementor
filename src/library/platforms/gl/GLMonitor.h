//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_MONITOR_H
#define ELEMENTOR_GL_MONITOR_H

#include "elementor.h"

#include "GLFW/glfw3.h"

namespace elementor::platforms::gl {
	class GLMonitor : public Monitor {
	public:
		GLMonitor(GLFWmonitor* monitor);

		Size getSize() override;

		Size getPhysicalSize() override;

	private:
		Size size;
		Size physicalSize;
	};
};

#endif //ELEMENTOR_GL_MONITOR_H

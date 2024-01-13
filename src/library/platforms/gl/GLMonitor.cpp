//
// Created by noartem on 15.08.2022.
//

#include "GLMonitor.h"
#include "utility.h"

namespace elementor::platforms::gl {
	GLMonitor::GLMonitor(GLFWmonitor* monitor) {
		this->size = getMonitorSize(monitor);
		this->physicalSize = getMonitorPhysicalSize(monitor);
	}

	Size GLMonitor::getSize() {
		return this->size;
	}

	Size GLMonitor::getPhysicalSize() {
		return this->physicalSize;
	}
}

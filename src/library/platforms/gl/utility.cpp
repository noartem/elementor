//
// Created by noartem 15.08.2022.
//

#include "utility.h"
#include "../../debug.h"

#include <algorithm>

namespace elementor::platforms::gl {
	Size getWindowSize(GLFWwindow* window) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		return {
			.width = (float)width,
			.height = (float)height
		};
	}

	Position getWindowPosition(GLFWwindow* window) {
		int x, y;
		glfwGetWindowPos(window, &x, &y);
		return {
			.x = (float)x,
			.y = (float)y
		};
	}

	Rect getWindowRect(GLFWwindow* window) {
		return {
			.size = getWindowSize(window),
			.position = getWindowPosition(window)
		};
	}

	Size getMonitorSize(GLFWmonitor* monitor) {
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		return {
			.width = (float)mode->width,
			.height = (float)mode->height
		};
	}

	Size getMonitorPhysicalSize(GLFWmonitor* monitor) {
		int width, height;
		glfwGetMonitorPhysicalSize(monitor, &width, &height);
		return {
			.width = (float)width,
			.height = (float)height
		};
	}

	Position getMonitorPosition(GLFWmonitor* monitor) {
		int x, y;
		glfwGetMonitorPos(monitor, &x, &y);
		return {
			.x = (float)x,
			.y = (float)y
		};
	}

	Rect getMonitorRect(GLFWmonitor* monitor) {
		return { getMonitorSize(monitor), getMonitorPosition(monitor) };
	}

	GLFWmonitor* getWindowMonitor(GLFWwindow* window) {
		Rect windowRect = getWindowRect(window);

		int monitorsSize = 0;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorsSize);

		GLFWmonitor* closestMonitor;
		int maxOverlapArea = 0;

		for (unsigned int i = 0; i < monitorsSize; i++) {
			GLFWmonitor* monitor = monitors[i];
			Rect monitorRect = getMonitorRect(monitor);

			float overlapWidth =
					windowRect.size.width - std::max((monitorRect.position.x - windowRect.position.x), 0.0f) - std::max(
							(windowRect.position.x + windowRect.size.width) -
							(monitorRect.position.x + monitorRect.size.width), 0.0f);
			float overlapHeight =
					windowRect.size.height - std::max((monitorRect.position.y - windowRect.position.y), 0.0f) -
					std::max((windowRect.position.y + windowRect.size.height) -
							 (monitorRect.position.y + monitorRect.size.height), 0.0f);
			float overlapArea = overlapWidth * overlapHeight;
			if (overlapArea > maxOverlapArea) {
				closestMonitor = monitor;
				maxOverlapArea = overlapArea;
			}
		}

		return closestMonitor;
	}
}

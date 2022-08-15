//
// Created by noartem on 15.08.2022.
//

#include "GLMonitor.h"
#include "utility.h"

namespace elementor {
    float calcMonitorPixelScale(Size pixelSize, Size physicalSize) {
        return (pixelSize.width / physicalSize.width) / DefaultMonitorScale;
    }

    GLMonitor::GLMonitor(GLFWmonitor *monitor) {
        this->size = getMonitorSize(monitor);
        this->physicalSize = getMonitorPhysicalSize(monitor);
        this->pixelScale = calcMonitorPixelScale(this->size, this->physicalSize);
    }

    Size GLMonitor::getSize() {
        return this->size;
    }

    Size GLMonitor::getPhysicalSize() {
        return this->physicalSize;
    }

    float GLMonitor::getPixelScale() {
        return this->pixelScale;
    }

    void GLMonitor::setPixelScale(float scale) {
        this->pixelScale = scale;
    }
}

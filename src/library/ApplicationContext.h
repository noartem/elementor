//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_APPLICATION_CONTEXT_H
#define ELEMENTOR_APPLICATION_CONTEXT_H

#include "Render.h"

namespace elementor {
    // Default monitor scale is 38 logical pixels per centimeter
    #define DefaultMonitorScale 3.8;

    struct ApplicationContext {
        Size windowSize;
        Size monitorPhysicalSize;
        float monitorPixelScale;
    };
}

#endif //ELEMENTOR_APPLICATION_CONTEXT_H
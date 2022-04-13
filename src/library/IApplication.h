//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_IAPPLICATION_H
#define ELEMENTOR_IAPPLICATION_H

#include <include/core/SkCanvas.h>

namespace elementor {
    class IApplication {
    public:
        virtual void draw(SkCanvas *canvas) = 0;
    };
}

#endif //ELEMENTOR_IAPPLICATION_H

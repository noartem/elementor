//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_APPLICATION_H
#define ELEMENTOR_APPLICATION_H

#include "Element.h"

namespace elementor {
    class Application {
    public:
        Element *root;

        void draw(SkCanvas *canvas, RenderSize size);
    };
};


#endif //ELEMENTOR_APPLICATION_H

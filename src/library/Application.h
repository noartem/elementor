//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_APPLICATION_H
#define ELEMENTOR_APPLICATION_H

#include "IApplication.h"

namespace elementor {
    class Application : IApplication {
    public:
        void draw(SkCanvas *canvas);
    };
};


#endif //ELEMENTOR_APPLICATION_H

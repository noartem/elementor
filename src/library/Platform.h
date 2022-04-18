//
// Created by noartem on 14.04.2022.
//

#ifndef ELEMENTOR_PLATFORM_H
#define ELEMENTOR_PLATFORM_H

#include "Application.h"

#include <optional>

namespace elementor {
    class Platform {
    public:
        std::string title;
        RenderSize size;
        std::optional <RenderSize> minSize;
        std::optional <RenderSize> maxSize;
        Application *application;

        int run();

    private:
        void draw(SkCanvas *canvas, RenderSize size);
    };
};


#endif //ELEMENTOR_PLATFORM_H

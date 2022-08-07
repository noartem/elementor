//
// Created by noartem on 07.08.2022.
//

#ifndef ELEMENTOR_COLOR_H
#define ELEMENTOR_COLOR_H

#include <include/core/SkColor.h>
#include <string>

namespace elementor {
    SkColor makeSkColorFromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    SkColor makeSkColorFromRGB(uint8_t r, uint8_t g, uint8_t b);

    SkColor makeSkColorFromHex(std::string hex);
}

#endif //ELEMENTOR_COLOR_H
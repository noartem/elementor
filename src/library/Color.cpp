//
// Created by noartem 07.08.2022.
//

#include "Color.h"

namespace elementor {
    SkColor makeSkColorFromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        return SkColorSetARGB(a, r, g, b);
    }

    SkColor makeSkColorFromRGB(uint8_t r, uint8_t g, uint8_t b) {
        return SkColorSetARGB(255, r, g, b);
    }

    SkColor makeSkColorFromHex(std::string hex) {
        if (hex.size() == 7 || hex.size() == 4) {
            hex = hex.substr(1);
        }

        if (hex.size() == 6) {
            uint8_t r = std::stoul(hex.substr(0, 2), nullptr, 16);
            uint8_t g = std::stoul(hex.substr(2, 2), nullptr, 16);
            uint8_t b = std::stoul(hex.substr(4, 2), nullptr, 16);
            return makeSkColorFromRGB(r, g, b);
        }

        if (hex.size() == 3) {
            uint8_t r = std::stoul(hex.substr(0, 1), nullptr, 16);
            r = r * 16 + r;
            uint8_t g = std::stoul(hex.substr(1, 1), nullptr, 16);
            g = g * 16 + g;
            uint8_t b = std::stoul(hex.substr(2, 1), nullptr, 16);
            b = b * 16 + b;
            return makeSkColorFromRGB(r, g, b);
        }

        return SK_ColorTRANSPARENT;
    }
}

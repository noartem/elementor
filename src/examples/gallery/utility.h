//
// Created by noartem on 29.05.2022.
//

#ifndef GALLERY_EXAMPLES_UTILITY_H
#define GALLERY_EXAMPLES_UTILITY_H

#include "elementor.h"

Element *box(std::string color);

Element *boxSized(std::string color, int width, int height);

int randInRange(int min, int max);

std::string floatToString(float value, int precision = 1);

void openURL(std::string url);

#endif //GALLERY_EXAMPLES_UTILITY_H

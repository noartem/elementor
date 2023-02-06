//
// Created by noartem on 29.05.2022.
//

#ifndef GALLERY_EXAMPLES_UTILITY_H
#define GALLERY_EXAMPLES_UTILITY_H

#include "elementor.h"

std::shared_ptr<Element> box(std::string color);

std::shared_ptr<Element> boxSized(std::string color, int width, int height);

int randInRange(int min, int max);

std::string floatToString(float value, int precision = 1);

#endif //GALLERY_EXAMPLES_UTILITY_H

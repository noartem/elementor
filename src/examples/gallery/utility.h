//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_EXAMPLES_UTILITY_H
#define ELEMENTOR_EXAMPLES_UTILITY_H

#include "../library/utility.h"
#include "../library/elements/utility.h"

using namespace elementor;
using namespace elementor::elements;

Element *box(std::string color);

Element *boxSized(std::string color, int width, int height);

int randInRange(int min, int max);

#endif //ELEMENTOR_EXAMPLES_UTILITY_H

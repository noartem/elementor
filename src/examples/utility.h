//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_EXAMPLES_UTILITY_H
#define ELEMENTOR_EXAMPLES_UTILITY_H

#include "../library/utility.h"

using namespace elementor;

class Example {
public:
    virtual std::string getName() = 0;

    virtual std::string getDescription() = 0;

    virtual Element *getScene() = 0;
};

#endif //ELEMENTOR_EXAMPLES_UTILITY_H

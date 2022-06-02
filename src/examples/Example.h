//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_EXAMPLE_H
#define ELEMENTOR_EXAMPLE_H

#include "utility.h"

class Example {
public:
    virtual std::string getName() = 0;

    virtual std::string getDescription() = 0;

    virtual Element *getScene() = 0;
};

#endif //ELEMENTOR_EXAMPLE_H

//
// Created by noartem on 30.05.2022.
//

#ifndef ELEMENTOR_EXAMPLE_WRAP_H
#define ELEMENTOR_EXAMPLE_WRAP_H

#include "utility.h"
#include "Example.h"

class ExampleWrap: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;
};


#endif //ELEMENTOR_EXAMPLE_WRAP_H
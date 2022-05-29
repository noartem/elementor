//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_EXAMPLE_FLEX_CHILDREN_H
#define ELEMENTOR_EXAMPLE_FLEX_CHILDREN_H

#include "Example.h"

class ExampleFlexChildren: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;
};


#endif //ELEMENTOR_EXAMPLE_FLEX_CHILDREN_H

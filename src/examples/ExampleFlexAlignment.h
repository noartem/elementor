//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_EXAMPLE_FLEX_ALIGNMENT_H
#define ELEMENTOR_EXAMPLE_FLEX_ALIGNMENT_H

#include "utility.h"

class ExampleFlexAlignment: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;
};


#endif //ELEMENTOR_EXAMPLE_FLEX_ALIGNMENT_H

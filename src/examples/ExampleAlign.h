//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_EXAMPLE_ALIGN_H
#define ELEMENTOR_EXAMPLE_ALIGN_H

#include "utility.h"
#include "Example.h"

class ExampleAlign: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;
};


#endif //ELEMENTOR_EXAMPLE_ALIGN_H
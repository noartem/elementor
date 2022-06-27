//
// Created by noartem on 11.06.2022.
//

#ifndef ELEMENTOR_EXAMPLE_TEXT_H
#define ELEMENTOR_EXAMPLE_TEXT_H

#include "utility.h"
#include "Example.h"

class ExampleText: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;
};


#endif //ELEMENTOR_EXAMPLE_TEXT_H
//
// Created by noartem on 25.08.2022.
//

#ifndef GALLERY_EXAMPLE_TEXT_INPUT_H
#define GALLERY_EXAMPLE_TEXT_INPUT_H

#include "utility.h"
#include "Example.h"

class ExampleTextInput: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;
};


#endif //GALLERY_EXAMPLE_TEXT_INPUT_H
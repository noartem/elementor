//
// Created by noartem on 30.05.2022.
//

#ifndef GALLERY_EXAMPLE_WRAP_H
#define GALLERY_EXAMPLE_WRAP_H

#include "utility.h"
#include "Example.h"

class ExampleWrap: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;
};


#endif //GALLERY_EXAMPLE_WRAP_H

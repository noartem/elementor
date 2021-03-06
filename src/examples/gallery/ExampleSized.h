//
// Created by noartem on 18.06.2022.
//

#ifndef GALLERY_EXAMPLE_SIZED_H
#define GALLERY_EXAMPLE_SIZED_H

#include "utility.h"
#include "Example.h"

class ExampleSized: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;
};


#endif //GALLERY_EXAMPLE_SIZED_H

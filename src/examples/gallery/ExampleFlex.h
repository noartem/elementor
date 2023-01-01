//
// Created by noartem on 30.05.2022.
//

#ifndef GALLERY_EXAMPLE_FLEX_H
#define GALLERY_EXAMPLE_FLEX_H

#include "utility.h"
#include "Example.h"

class ExampleFlex: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene(ApplicationContext *ctx) override;
};


#endif //GALLERY_EXAMPLE_FLEX_H

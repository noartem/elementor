//
// Created by noartem on 11.06.2022.
//

#ifndef GALLERY_EXAMPLE_TEXT_H
#define GALLERY_EXAMPLE_TEXT_H

#include "utility.h"
#include "Example.h"

class ExampleText: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene(ApplicationContext *ctx) override;
};


#endif //GALLERY_EXAMPLE_TEXT_H
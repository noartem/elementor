//
// Created by noartem on 29.05.2022.
//

#ifndef GALLERY_EXAMPLE_H
#define GALLERY_EXAMPLE_H

#include "utility.h"

class Example {
public:
    virtual std::string getName() = 0;

    virtual std::string getDescription() = 0;

    virtual Element *getScene() = 0;
};

#endif //GALLERY_EXAMPLE_H

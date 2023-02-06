//
// Created by noartem on 03.02.2023.
//

#ifndef GALLERY_EXAMPLE_STACK_H
#define GALLERY_EXAMPLE_STACK_H

#include "utility.h"
#include "Example.h"

class ExampleStack: public Example {
    std::string getName() override;

    std::string getDescription() override;

    std::shared_ptr<Element> getScene(std::shared_ptr<ApplicationContext> ctx) override;
};


#endif //GALLERY_EXAMPLE_STACK_H
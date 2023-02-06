//
// Created by noartem on 03.02.2023.
//

#ifndef GALLERY_EXAMPLE_BUTTON_H
#define GALLERY_EXAMPLE_BUTTON_H

#include "utility.h"
#include "Example.h"

class ExampleButton: public Example {
    std::string getName() override;

    std::string getDescription() override;

    std::shared_ptr<Element> getScene(std::shared_ptr<ApplicationContext> ctx) override;
};


#endif //GALLERY_EXAMPLE_BUTTON_H
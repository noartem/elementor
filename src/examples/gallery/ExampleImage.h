//
// Created by noartem on 26.07.2022.
//

#ifndef GALLERY_EXAMPLE_IMAGE_H
#define GALLERY_EXAMPLE_IMAGE_H

#include "utility.h"
#include "Example.h"

class ExampleImage: public Example {
    std::string getName() override;

    std::string getDescription() override;

    std::shared_ptr<Element> getScene(std::shared_ptr<ApplicationContext> ctx) override;
};


#endif //GALLERY_EXAMPLE_IMAGE_H

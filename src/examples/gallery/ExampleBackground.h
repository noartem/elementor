//
// Created by noartem on 02.06.2022.
//

#ifndef GALLERY_EXAMPLE_BACKGROUND_H
#define GALLERY_EXAMPLE_BACKGROUND_H

#include "utility.h"
#include "Example.h"

class ExampleBackground: public Example {
    std::string getName() override;

    std::string getDescription() override;

    std::shared_ptr<Element> getScene(std::shared_ptr<ApplicationContext> ctx) override;
};


#endif //GALLERY_EXAMPLE_BACKGROUND_H

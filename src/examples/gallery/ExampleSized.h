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

    std::shared_ptr<Element> getScene(std::shared_ptr<ApplicationContext> ctx) override;
};


#endif //GALLERY_EXAMPLE_SIZED_H

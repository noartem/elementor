//
// Created by noartem on 29.05.2022.
//

#ifndef GALLERY_EXAMPLE_ALIGN_H
#define GALLERY_EXAMPLE_ALIGN_H

#include "utility.h"
#include "elementor.h"
#include "Example.h"

class ExampleAlign: public Example {
    std::string getName() override;

    std::string getDescription() override;

    std::shared_ptr<Element> getScene(std::shared_ptr<ApplicationContext> ctx) override;
};


#endif //GALLERY_EXAMPLE_ALIGN_H

//
// Created by noartem on 03.06.2022.
//

#ifndef GALLERY_EXAMPLES_H
#define GALLERY_EXAMPLES_H

#include "Example.h"

#include "ExampleBackground.h"
#include "ExampleText.h"
#include "ExampleSized.h"
#include "ExampleImage.h"
#include "ExampleAlign.h"
#include "ExampleFlex.h"
#include "ExampleWrap.h"

std::vector<Example *> examples() {
    return {
        new ExampleBackground(),
        new ExampleText(),
        new ExampleSized(),
        new ExampleImage(),
        new ExampleAlign(),
        new ExampleFlex(),
        new ExampleWrap(),
    };
}


#endif //GALLERY_EXAMPLES_H

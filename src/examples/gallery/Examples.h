//
// Created by noartem on 03.06.2022.
//

#ifndef ELEMENTOR_EXAMPLES_H
#define ELEMENTOR_EXAMPLES_H

#include "Example.h"

#include "ExampleBackground.h"
#include "ExampleText.h"
#include "ExampleSized.h"
#include "ExampleAlign.h"
#include "ExampleFlex.h"
#include "ExampleWrap.h"

std::vector<Example *> examples() {
    return {
        new ExampleBackground(),
        new ExampleText(),
        new ExampleSized(),
        new ExampleAlign(),
        new ExampleFlex(),
        new ExampleWrap(),
    };
}


#endif //ELEMENTOR_EXAMPLES_H

//
// Created by noartem on 03.06.2022.
//

#ifndef GALLERY_EXAMPLES_H
#define GALLERY_EXAMPLES_H

#include "Example.h"

#include "ExampleBackground.h"
#include "ExampleButton.h"
#include "ExampleText.h"
#include "ExampleTextInput.h"
#include "ExampleSized.h"
#include "ExampleImage.h"
#include "ExampleAlign.h"
#include "ExampleFlex.h"
#include "ExampleStack.h"
#include "ExampleWrap.h"
#include "ExampleAnimation.h"

std::vector<Example *> examples() {
    return {
            new ExampleBackground(),
            new ExampleButton(),
            new ExampleText(),
            new ExampleTextInput(),
            new ExampleSized(),
            new ExampleImage(),
            new ExampleAlign(),
            new ExampleFlex(),
            new ExampleStack(),
            new ExampleWrap(),
            new ExampleAnimation(),
    };
}


#endif //GALLERY_EXAMPLES_H

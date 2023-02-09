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

std::vector<std::shared_ptr<Example>> examples() {
    return {
            std::make_shared<ExampleBackground>(),
            std::make_shared<ExampleButton>(),
            std::make_shared<ExampleText>(),
            std::make_shared<ExampleTextInput>(),
            std::make_shared<ExampleSized>(),
            std::make_shared<ExampleImage>(),
            std::make_shared<ExampleAlign>(),
            std::make_shared<ExampleFlex>(),
            std::make_shared<ExampleStack>(),
            std::make_shared<ExampleWrap>(),
            std::make_shared<ExampleAnimation>(),
    };
}


#endif //GALLERY_EXAMPLES_H

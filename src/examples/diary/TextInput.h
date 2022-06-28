//
// Created by noartem on 28.06.2022.
//

#ifndef DIARY_TEXT_INPUT_H
#define DIARY_TEXT_INPUT_H

#include "utility.h"

class TextInput : public Element {
public:
    TextInput();

    Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

private:
    Element *child;
    bool focused;
};

TextInput *textInput();

#endif //DIARY_TEXT_INPUT_H

//
// Created by noartem on 28.06.2022.
//

#ifndef DIARY_TEXT_INPUT_H
#define DIARY_TEXT_INPUT_H

#include "utility.h"

class TextInput : public Element {
public:
    TextInput();

    std::string getValue();

    TextInput *onChange(std::function<std::string (std::string text)> callback);

    Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

private:
    Element *child;
    std::string value;
    bool focused;
    std::function<std::string (std::string text)> callbackChange;
};

TextInput *textInput();

#endif //DIARY_TEXT_INPUT_H

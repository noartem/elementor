//
// Created by noartem on 25.08.2022.
//

#ifndef GALLERY_TEXT_INPUT_H
#define GALLERY_TEXT_INPUT_H

#include "elementor.h"

class TextInput : public Element {
public:
    TextInput();

    TextInput *setValue(std::u32string value);

    std::u32string getValue();

    TextInput *onChange(std::function<std::u32string (std::u32string text)> callback);

    Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

private:
    Element *child;
    Inputable *inputableChild;
    std::u32string value;
    bool focused;
    std::function<std::u32string (std::u32string text)> callbackChange;
};

TextInput *textInput();

#endif //GALLERY_TEXT_INPUT_H

//
// Created by noartem on 25.08.2022.
//

#ifndef GALLERY_TEXT_INPUT_H
#define GALLERY_TEXT_INPUT_H

#include "utility.h"

class TextInput : public Component {
public:
    TextInput();

    TextInput *setValue(std::u32string value);

    std::u32string getValue();

    TextInput *onChange(std::function<std::u32string (std::u32string text)> callback);

private:
    Inputable *inputableChild;
    std::u32string value;
    bool focused;
    std::function<std::u32string (std::u32string text)> callbackChange;
};

TextInput *textInput();

#endif //GALLERY_TEXT_INPUT_H

//
// Created by noartem on 28.06.2022.
//

#ifndef DIARY_TEXT_INPUT_H
#define DIARY_TEXT_INPUT_H

#include "elementor.h"

class TextInput : public Element {
public:
    TextInput();

    TextInput *setValue(std::u32string value);

    std::u32string getValue();

    TextInput *onChange(std::function<std::u32string (std::u32string text)> callback);

    Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

private:
    std::shared_ptr<Element> child;
    std::shared_ptr<Inputable>inputableChild;
    std::u32string value;
    bool focused;
    std::function<std::u32string (std::u32string text)> callbackChange;
};

TextInput *textInput();

#endif //DIARY_TEXT_INPUT_H

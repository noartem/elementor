//
// Created by noartem on 25.08.2022.
//

#ifndef ELEMENTOR_COMPONENTS_TEXT_INPUT_H
#define ELEMENTOR_COMPONENTS_TEXT_INPUT_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class TextInput : public Component, public std::enable_shared_from_this<TextInput> {
    public:
        TextInput();

        std::shared_ptr<TextInput> setValue(const std::u32string &newValue);

        std::u32string getValue();

        std::shared_ptr<TextInput> onChange(std::function<std::u32string(std::u32string text)> callback);

    private:
        std::shared_ptr<Inputable> inputableChild;
        std::u32string value;
        bool focused;
        std::function<std::u32string(std::u32string text)> callbackChange;
    };

    std::shared_ptr<TextInput> textInput();
}

#endif //ELEMENTOR_COMPONENTS_TEXT_INPUT_H

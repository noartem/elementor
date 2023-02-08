//
// Created by noartem on 03.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_BUTTON_H
#define ELEMENTOR_COMPONENTS_BUTTON_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class Button : public Component, public std::enable_shared_from_this<Button> {
    public:
        Button();

        std::shared_ptr<Button> setLabel(std::u32string newLabel);

        std::shared_ptr<Button> setLabel(std::string newLabel);

        std::string getLabel();

        std::shared_ptr<Button> onClick(const std::function<void()>& callback);

        std::shared_ptr<Button> setBackgroundColor(std::string hex);

        std::shared_ptr<Button> setTextColor(std::string hex);

    private:
        std::string label;
        std::shared_ptr<Clickable> clickableElement;
        std::shared_ptr<Text> textElement;
        std::shared_ptr<Background> backgroundElement;
    };

    std::shared_ptr<Button> button();
}

#endif //ELEMENTOR_COMPONENTS_BUTTON_H

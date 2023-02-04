//
// Created by noartem on 03.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_BUTTON_H
#define ELEMENTOR_COMPONENTS_BUTTON_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
    class Button : public Component {
    public:
        Button();

        Button *setLabel(std::u32string newLabel);

        Button *setLabel(std::string newLabel);

        std::string getLabel();

        Button *onClick(std::function<void()> callback);

        Button *setBackgroundColor(std::string hex);

        Button *setTextColor(std::string hex);

    private:
        std::string label;
        Clickable *clickableElement;
        Text *textElement;
        Background *backgroundElement;
    };

    Button *button();
}

#endif //ELEMENTOR_COMPONENTS_BUTTON_H

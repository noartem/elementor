//
// Created by noartem on 03.02.2023.
//

#ifndef GALLERY_COMPONENTS_BUTTON_H
#define GALLERY_COMPONENTS_BUTTON_H

#include "../utility.h"

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

#endif //GALLERY_COMPONENTS_BUTTON_H
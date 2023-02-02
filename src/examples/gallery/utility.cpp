//
// Created by noartem on 02.06.2022.
//

#include "utility.h"

Element *box(std::string color) {
    return rounded()
        ->setRadius(8)
        ->setChild(background()
            ->setColor(color));
}

Element *boxSized(std::string color, int boxWidth, int boxHeight) {
    return width()
        ->setWidth(boxWidth)
        ->setChild(height()
            ->setHeight(boxHeight)
            ->setChild(box(color)));
}

int randInRange(int min, int max) {
    return min + (std::rand() % (max - min + 1));
}

std::string floatToString(float value, int precision) {
    std::string text = std::to_string(value);
    return text.substr(0, text.find(".") + precision + 1);
}

void openURL(std::string url) {
    #if defined(OS_HOST_WINDOWS)
        std::string command = "start " + url;
    #elif defined(OS_HOST_LINUX)
        std::string command = "xdg-open " + url;
    #elif defined(OS_HOST_MACOS)
        std::string command = "open " + url;
    #endif

    system(command.c_str());
}

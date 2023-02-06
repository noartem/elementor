//
// Created by noartem on 02.06.2022.
//

#include "utility.h"

std::shared_ptr<Element> box(std::string color) {
    return rounded()
        ->setRadius(8)
        ->setChild(background()
            ->setColor(color));
}

std::shared_ptr<Element> boxSized(std::string color, int boxWidth, int boxHeight) {
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

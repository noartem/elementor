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
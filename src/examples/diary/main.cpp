//
// Created by noartem on 27.06.2022.
//

#include "utility.h"

int main() {
    Application *application = new Application();
    application->root = background()
        ->setColor("#FFFCF3");

    Platform *platform = new Platform();
    platform->title = "Diary";
    platform->size = {920, 640};
    platform->minSize = {640, 320};
    platform->application = application;

    platform->run();
}
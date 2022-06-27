//
// Created by noartem on 28.05.2022.
//

#include "utility.h"
#include "ExamplesGallery.h"

int main() {
    Application *application = new Application();
    application->root = new ExamplesGallery();

    Platform *platform = new Platform();
    platform->title = "Elementor examples";
    platform->size = {920, 640};
    platform->minSize = {640, 320};
    platform->application = application;

    platform->run();
}
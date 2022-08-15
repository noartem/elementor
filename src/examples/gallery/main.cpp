//
// Created by noartem on 28.05.2022.
//

#include "utility.h"
#include "ExamplesGallery.h"

int main() {
    GLPlatform *platform = new GLPlatform();
    GLWindow *window = platform->makeWindow();
    window->setTitle("Elementor Examples");
    window->setRoot(new ExamplesGallery());
    window->setSize({920, 640});
    window->setMinSize({630, 320});
    platform->run();
}
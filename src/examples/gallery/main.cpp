//
// Created by noartem on 28.05.2022.
//

#include "utility.h"
#include "ExamplesGallery.h"

int main() {
    auto *platform = new GLPlatform();
    auto *window = platform->makeWindow();
    window->setTitle("Elementor Examples");
    auto rootElement = new ExamplesGallery();
    auto componentsContext = new ComponentsContext(rootElement);
    window->setUserPointer(componentsContext);
    window->setRoot(componentsContext);
    window->setSize({920, 640});
    window->setMinSize({630, 320});
    platform->run();
}
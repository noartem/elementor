//
// Created by noartem on 28.05.2022.
//

#include "utility.h"
#include "ExamplesGallery.h"

int main() {
    auto platform = std::make_shared<GLPlatform>();
    auto window = platform->makeWindow({920, 640});
    window->setTitle("Elementor Examples");
//    auto rootElement = std::make_shared<ExamplesGallery>();
    auto rootElement = background()
            ->setColor("#FFAAAA");
    auto componentsContext = std::make_shared<ComponentsContext>(rootElement);
    window->setUserPointer(componentsContext);
    window->setRoot(componentsContext);
    window->setMinSize({630, 320});
    platform->run();
}
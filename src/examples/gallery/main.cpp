//
// Created by noartem on 28.05.2022.
//

#include "utility.h"
#include "ExamplesGallery.h"

int main() {
    glApplication()
        ->setTitle("Elementor Examples")
        ->setRoot(new ExamplesGallery())
        ->setDefaultSize({920, 640})
        ->setMinSize({630, 320})
        ->run();
}
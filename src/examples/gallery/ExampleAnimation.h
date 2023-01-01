//
// Created by noartem on 01.01.2023.
//

#ifndef GALLERY_EXAMPLE_ANIMATION_H
#define GALLERY_EXAMPLE_ANIMATION_H

#include "utility.h"
#include "Example.h"

class ExampleAnimation: public Example {
    std::string getName() override;

    std::string getDescription() override;

    Element *getScene(ApplicationContext *ctx) override;
};

class AnimatedButton: public Element {
public:
    AnimatedButton(std::string label, int duration);

    Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

    std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

private:
    ApplicationContext *ctx;
    std::string label;
    int duration;
    Element *button;
    Background *buttonBackground;
    Text *buttonText;
    Animation<std::chrono::milliseconds> *buttonAnimation = NULL;

    Element *makeElement();
};

#endif //GALLERY_EXAMPLE_ANIMATION_H
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

class AnimatedTextExample: public Component {
public:
    AnimatedTextExample(std::string label, int duration) {
        this->label = label;
        this->duration = duration;
        render();
    }

private:
    std::string label;
    int duration;
    Background *buttonBackground;
    Text *buttonText;
    Animation<std::chrono::milliseconds> *buttonAnimation = NULL;

    void render();
};

class AnimatedPositionExample: public Component {
public:
    AnimatedPositionExample(std::string label, int duration) {
        this->label = label;
        this->duration = duration;
        render();
    }

private:
    std::string label;
    int duration;
    Background *buttonBackground;
    Text *buttonText;
    Padding *buttonPadding;
    Animation<std::chrono::milliseconds> *buttonAnimation = NULL;

    void render();
};

#endif //GALLERY_EXAMPLE_ANIMATION_H
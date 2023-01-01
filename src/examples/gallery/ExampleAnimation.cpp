//
// Created by noartem on 01.01.2023.
//

#include "ExampleAnimation.h"
#include "Scroll.h"

std::string ExampleAnimation::getName() {
    return "Animation";
}

std::string ExampleAnimation::getDescription() {
    return "Element changes made smooth";
}

AnimatedButton::AnimatedButton(std::string label, int duration) {
    this->label = label;
    this->duration = duration;
    this->button = this->makeElement();
}

Size AnimatedButton::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
    return this->button->getSize(ctx, window, boundaries);
}

std::vector <RenderElement> AnimatedButton::getChildren(ApplicationContext *ctx, Window *window, Size size) {
    this->ctx = ctx;
    RenderElement buttonElement;
    buttonElement.element = this->button;
    buttonElement.position = {0, 0};
    buttonElement.size = size;
    return {buttonElement};
}

Element *AnimatedButton::makeElement() {
    this->buttonBackground = background();

    this->buttonText = text()
        ->setFontColor("#006C4C")
        ->setFontSize(16)
        ->setFontWeight(450)
        ->setFontFamily("Fira Code")
        ->setText(this->label);

    return clickable()
        ->setChild(hoverable()
            ->setChild(width()
                ->setWidth(80)
                ->setChild(
                    rounded()
                    ->setRadius(8)
                    ->setChild(this->buttonBackground
                        ->setColor("#DEEDE6")
                        ->setChild(padding()
                            ->setPaddings(12, 18)
                            ->setChild(height()
                                ->setHeight(14)
                                ->setChild(alignWidth()
                                    ->setCoef(0.5, 0.5)
                                    ->setChild(this->buttonText)))))))
            ->onEnter([this] () { this->buttonBackground->setColor("#C2DDD3"); })
            ->onLeave([this] () { this->buttonBackground->setColor("#DEEDE6"); }))
        ->onClick([this] () {
            if (this->buttonAnimation != NULL) {
                this->buttonAnimation->stop();
            }

            this->buttonAnimation = animation(ctx, this->duration, [this] (float state) {
                if (state < ONE) {
                    this->buttonText->setText(std::to_string((int) (state * 100)) + "%");
                } else {
                    this->buttonText->setText(this->label);
                }
            });

            this->buttonAnimation->start();
        });
}

Element *ExampleAnimation::getScene(ApplicationContext *ctx) {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(12)
                ->appendChild(alignWidth()
                    ->setChild(new AnimatedButton("0.5s", 500)))
                ->appendChild(alignWidth()
                    ->setChild(new AnimatedButton("1s", 1000)))
                ->appendChild(alignWidth()
                    ->setChild(new AnimatedButton("5s", 5000)))
                ->appendChild(alignWidth()
                    ->setChild(new AnimatedButton("10s", 10000)))));
}

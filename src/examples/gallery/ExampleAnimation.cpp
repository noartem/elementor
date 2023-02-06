//
// Created by noartem on 01.01.2023.
//

#include "ExampleAnimation.h"

std::string ExampleAnimation::getName() {
    return "Animation";
}

std::string ExampleAnimation::getDescription() {
    return "Element changes made smooth";
}

void AnimatedTextExample::render() {
    this->buttonBackground = background();

    this->buttonText = text()
        ->setFontColor("#006C4C")
        ->setFontSize(16)
        ->setFontWeight(450)
        ->setFontFamily("Fira Code")
        ->setText(this->label);

    this->element = clickable()
        ->setChild(hoverable()
            ->setChild(width()
                ->setWidth(80)
                ->setChild(rounded()
                    ->setRadius(8)
                    ->setChild(this->buttonBackground
                        ->setColor("#DEEDE6")
                        ->setChild(padding()
                            ->setPaddings(12, 18)
                            ->setChild(height()
                                ->setHeight(12)
                                ->setChild(alignWidth()
                                    ->setCoef(0.5, 0.5)
                                    ->setChild(this->buttonText)))))))
            ->onEnter([this] () { this->buttonBackground->setColor("#C2DDD3"); })
            ->onLeave([this] () { this->buttonBackground->setColor("#DEEDE6"); }))
        ->onClick([this] () {
            if (this->buttonAnimation != NULL) {
                this->buttonAnimation->pause();
            }

            this->buttonAnimation = animation(this->ctx, this->duration, [this] (float state) {
                if (state < ONE) {
                    this->buttonText->setText(std::to_string((int) (state * 100)) + "%");
                } else {
                    this->buttonText->setText(this->label);
                }
            });

            this->buttonAnimation->play();
        });
}

void AnimatedPositionExample::render() {
    this->buttonBackground = background();

    this->buttonText = text()
        ->setFontColor("#006C4C")
        ->setFontSize(16)
        ->setFontWeight(450)
        ->setFontFamily("Fira Code")
        ->setText(this->label);

    this->buttonPadding = padding();

    this->element = clickable()
        ->setChild(this->buttonPadding
            ->setChild(hoverable()
                ->setChild(alignWidth()
                    ->setChild(width()
                    ->setWidth(80)
                    ->setChild(rounded()
                        ->setRadius(8)
                        ->setChild(this->buttonBackground
                            ->setColor("#DEEDE6")
                            ->setChild(padding()
                                ->setPaddings(12, 18)
                                ->setChild(height()
                                    ->setHeight(12)
                                    ->setChild(alignWidth()
                                        ->setCoef(0.5, 0.5)
                                        ->setChild(this->buttonText))))))))
                ->onEnter([this] () { this->buttonBackground->setColor("#C2DDD3"); })
                ->onLeave([this] () { this->buttonBackground->setColor("#DEEDE6"); })))
        ->onClick([this] () {
            if (this->buttonAnimation != nullptr) {
                this->buttonAnimation->pause();
                this->buttonAnimation = nullptr;
                return;
            }

            this->buttonAnimation = animation(this->ctx, this->duration, [this] (float value) {
                this->buttonText->setText(std::to_string((int) (value * 100)) + "%");
                auto paddingLeft = std::max((this->rect.size.width / ctx->getPixelScale()) - 80, ZERO) * value;
                this->buttonPadding->setPaddings(0, 0, 0, paddingLeft);
            });

            this->buttonAnimation->play();
        });
}

std::shared_ptr<Element> ExampleAnimation::getScene(std::shared_ptr<ApplicationContext> ctx) {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(12)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Text"))
                ->appendChild(alignWidth()
                    ->setChild(new AnimatedTextExample("0.5s", 500)))
                ->appendChild(alignWidth()
                    ->setChild(new AnimatedTextExample("1s", 1000)))
                ->appendChild(alignWidth()
                    ->setChild(new AnimatedTextExample("5s", 5000)))
                ->appendChild(alignWidth()
                    ->setChild(new AnimatedTextExample("10s", 10000)))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Position"))
                ->appendChild(expandedWidth()
                    ->setChild(new AnimatedPositionExample("0.5s", 500)))
                ->appendChild(expandedWidth()
                    ->setChild(new AnimatedPositionExample("1s", 1000)))
                ->appendChild(expandedWidth()
                    ->setChild(new AnimatedPositionExample("5s", 5000)))
                ->appendChild(expandedWidth()
                    ->setChild(new AnimatedPositionExample("10s", 10000)))));
}

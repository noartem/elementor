//
// Created by noartem on 03.06.2022.
//

#include "ExamplesGallery.h"
#include "Examples.h"
#include "components/Scroll.h"
#include "components/FPSLabel.h"
#include "components/ScaleControl.h"

ExamplesGallery::ExamplesGallery() {
    this->activeExampleElement = empty();
    this->activeExampleLabelName = empty();
    this->activeExampleLabelDescription = empty();

    this->scene = background()
        ->setColor("#FFFFFF")
        ->setChild(flex()
            ->appendChild(width()
                ->setWidth(200)
                    ->setChild(background()
                        ->setColor("#EDF5F0")
                        ->setChild(padding()
                            ->setPaddings(12, 18)
                            ->setChild(flex()
                                ->setSpacing(6)
                                ->setDirection(FlexDirection::Column)
                                ->appendChild(clickable()
                                    ->setChild(text()
                                        ->setFontColor("#191C1A")
                                        ->setFontSize(18)
                                        ->setFontWeight(500)
                                        ->setFontFamily("Fira Code")
                                        ->setText("Examples"))
                                    ->onClick([this] () {
                                        this->ctx->requestNextFrame([this] () {
                                            auto window = this->ctx->makeWindow();
                                            window->setTitle("Elementor Examples");
                                            window->setRoot(new ExamplesGallery());
                                            window->setSize({920, 640});
                                            window->setMinSize({630, 320});
                                        });
                                    }))
                                ->appendChild(empty())
                                ->appendChild(flexible()
                                    ->setChild(rounded()
                                        ->setRadius(8)
                                        ->setChild(scrollable()
                                            ->setChild(background()
                                                ->setColor("#DEEDE6")
                                                ->setChild(this->makeExamplesList())))))
                                ->appendChild(scaleControl())
                                ->appendChild(fpsLabel())))))
            ->appendChild(flexible()
                ->setGrow(3)
                ->setChild(flex()
                    ->setDirection(FlexDirection::Column)
                    ->appendChild(padding()
                        ->setPaddings(12, 18)
                        ->setChild(column()
                            ->setSpacing(8)
                            ->appendChild(height()
                                ->setHeight(16)
                                ->setChild(this->activeExampleLabelName))
                            ->appendChild(height()
                                ->setHeight(14)
                                ->setChild(this->activeExampleLabelDescription))))
                    ->appendChild(flexible()
                        ->setChild(this->activeExampleElement)))));
}

void ExamplesGallery::setActiveExample(Example *example) {
    this->activeExampleElement
        ->setChild(example->getScene(this->ctx));

    this->activeExampleLabelName
        ->setChild(text()
            ->setFontColor("#062016")
            ->setFontSize(16)
            ->setText(example->getName()));

    this->activeExampleLabelDescription
        ->setChild(text()
            ->setFontColor("#3F4944")
            ->setFontSize(14)
            ->setText(example->getDescription()));
}

Element *ExamplesGallery::makeExamplesList() {
    Column *examplesList = column();
    for (Example *example : examples()) {
        Background *buttonBackground = background();
        examplesList
            ->appendChild(clickable()
                ->setChild(hoverable()
                    ->setChild(buttonBackground
                        ->setColor("#DEEDE6")
                        ->setChild(padding()
                            ->setPaddings(16, 20)
                            ->setChild(text()
                                ->setFontColor("#006C4C")
                                ->setFontSize(16)
                                ->setFontWeight(450)
                                ->setFontFamily("Fira Code")
                                ->setText(example->getName()))))
                    ->onEnter([buttonBackground] () { buttonBackground->setColor("#C2DDD3"); })
                    ->onLeave([buttonBackground] () { buttonBackground->setColor("#DEEDE6"); }))
                ->onClick([this, example] () { this->setActiveExample(example); }));
    }

    return examplesList;
}

std::vector <RenderElement> ExamplesGallery::getChildren(ApplicationContext *ctx, Window *window, Size size) {
    this->ctx = ctx;
    RenderElement sceneElement;
    sceneElement.element = this->scene;
    sceneElement.position = {0, 0};
    sceneElement.size = size;
    return {sceneElement};
}

//
// Created by noartem on 03.06.2022.
//

#include "ExamplesGallery.h"
#include "Examples.h"
#include "Scroll.h"

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
                    ->setChild(flex()
                        ->setDirection(FlexDirection::Column)
                        ->appendChild(padding()
                            ->setPaddings(12, 18)
                            ->setChild(text()
                                ->setFontColor("#062016")
                                ->setFontSize(18)
                                ->setText("Examples")))
                        ->appendChild(flexible()
                            ->setChild(expandedWidth()
                                ->setChild(scroll()
                                    ->setChild(padding()
                                        ->setPaddings(12, 18)
                                        ->setChild(this->makeExamplesList()))))))))
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
        ->setChild(example->getScene());

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

Column *ExamplesGallery::makeExamplesList() {
    Column *examplesList = column();
    for (Example *example : examples()) {
        Background *buttonBackground = background();
        examplesList
            ->appendChild(clickable()
                ->setChild(hoverable()
                    ->setChild(rounded()
                        ->setRadius(24)
                        ->setChild(buttonBackground
                            ->setColor("#EDF5F0")
                            ->setChild(padding()
                                ->setPaddings(12, 18)
                                ->setChild(text()
                                    ->setFontColor("#062016")
                                    ->setFontSize(16)
                                    ->setText(example->getName())))))
                    ->onEnter([buttonBackground] () { buttonBackground->setColor("#CDE8D9"); })
                    ->onLeave([buttonBackground] () { buttonBackground->setColor("#EDF5F0"); }))
                ->onClick([this, example] () { this->setActiveExample(example); }));
    }

    return examplesList;
}

std::vector <RenderElement> ExamplesGallery::getChildren(ApplicationContext *ctx, Size size) {
    RenderElement sceneElement;
    sceneElement.element = this->scene;
    sceneElement.position = {0, 0};
    sceneElement.size = size;
    return {sceneElement};
}

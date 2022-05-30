//
// Created by noartem on 28.05.2022.
//

#include "utility.h"
#include "Scroll.h"

#include "ExampleFlexChildren.h"
#include "ExampleFlexAlignment.h"
#include "ExampleFlexCrossAlignment.h"
#include "ExampleAlign.h"

int main() {
    Example *examples[] = {
        new ExampleFlexChildren(),
        new ExampleFlexAlignment(),
        new ExampleFlexCrossAlignment(),
        new ExampleAlign(),
    };

    Empty *activeExampleElement = empty();

    Label *activeExampleLabelName = label()
        ->setFontColor("#062016")
        ->setFontSize(16);

    Label *activeExampleLabelDescription = label()
        ->setFontColor("#3F4944")
        ->setFontSize(14);

    Column *examplesList = column();
    for (Example *example : examples) {
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
                                ->setChild(label()
                                    ->setFontColor("#062016")
                                    ->setFontSize(16)
                                    ->setText(example->getName())))))
                    ->onEnter([buttonBackground] () { buttonBackground->setColor("#CDE8D9"); })
                    ->onLeave([buttonBackground] () { buttonBackground->setColor("#EDF5F0"); }))
                ->onClick([example, activeExampleElement, activeExampleLabelName, activeExampleLabelDescription] () {
                    activeExampleElement->setChild(example->getScene());
                    activeExampleLabelName->setText(example->getName());
                    activeExampleLabelDescription->setText(example->getDescription());
                }));
    }

    Application *application = new Application();
    application->root = background()
        ->setColor("#FFFCF3")
        ->setChild(flex()
            ->appendChild(flexible()
                ->setGrow(2)
                ->setChild(background()
                    ->setColor("#EDF5F0")
                    ->setChild(flex()
                        ->setDirection(FlexDirection::Column)
                        ->appendChild(padding()
                            ->setPaddings(12, 18)
                            ->setChild(label()
                                ->setFontColor("#062016")
                                ->setFontSize(18)
                                ->setText("Examples")))
                        ->appendChild(flexible()
                            ->setChild(scroll()
                                ->setChild(padding()
                                    ->setPaddings(12, 18)
                                    ->setChild(examplesList)))))))
            ->appendChild(flexible()
                ->setGrow(5)
                ->setChild(flex()
                    ->setDirection(FlexDirection::Column)
                    ->appendChild(padding()
                        ->setPaddings(12, 18)
                        ->setChild(column()
                            ->setSpacing(8)
                            ->appendChild(height()
                                ->setHeight(16)
                                ->setChild(activeExampleLabelName))
                            ->appendChild(height()
                                ->setHeight(14)
                                ->setChild(activeExampleLabelDescription))))
                    ->appendChild(flexible()
                        ->setChild(activeExampleElement)))));

    Platform *platform = new Platform();
    platform->title = "Elementor examples";
    platform->size = {920, 640};
    platform->minSize = {640, 320};
    platform->application = application;

    platform->run();
}
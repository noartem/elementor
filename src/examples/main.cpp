//
// Created by noartem on 28.05.2022.
//

#include "./Example.h"
#include "./ExampleFlexAlignment.h"
#include "./ExampleFlexChildren.h"

Element *scrollTrack() {
    return sized()->setSize(16, 16);
}

Element *scrollThumb() {
    return sized()
        ->setSize(16, 16)
        ->setChild(padding()
            ->setPaddings(4)
            ->setChild(rounded()
                ->setRadius(4)
                ->setChild(background()
                    ->setColor("#BBB9AE"))));
}

int main() {
    Example *examples[] = {
        new ExampleFlexChildren(),
        new ExampleFlexAlignment(),
    };

    Background *activeExampleElement = background();

    Column *examplesList = column();
    for (Example *example : examples) {
        Background *buttonBackground = background();
        examplesList
            ->appendChild(clickable()
                ->setChild(hoverable()
                    ->setChild(rounded()
                        ->setRadius(24)
                        ->setChild(buttonBackground
                            ->setColor("#F7F4E8")
                            ->setChild(padding()
                                ->setPaddings(12, 18)
                                ->setChild(label()
                                    ->setFontColor("#1C1D07")
                                    ->setFontSize(16)
                                    ->setText(example->getName())))))
                    ->onEnter([buttonBackground] () { buttonBackground->setColor("#E6E4C2"); })
                    ->onLeave([buttonBackground] () { buttonBackground->setColor("#F7F4E8"); }))
                ->onClick([example, activeExampleElement] () { activeExampleElement->setChild(example->getScene()); }));
    }

    Application *application = new Application();
    application->root = background()
        ->setColor("#FFFCF3")
        ->setChild(flex()
            ->setSpacing(12)
            ->appendChild(flexible()
                ->setGrow(1)
                ->setChild(background()
                    ->setColor("#F7F4E8")
                    ->setChild(scrollbar()
                        ->setScrollTrack(scrollTrack)
                        ->setScrollThumb(scrollThumb)
                        ->setChild(scrollable()
                            ->setDirection(ScrollDirection::Vertical)
                            ->setChild(padding()
                                ->setPaddings(18)
                                ->setChild(scrollbar()
                                    ->setChild(scrollable()
                                        ->setDirection(ScrollDirection::Vertical)
                                        ->setChild(examplesList))))))))
            ->appendChild(flexible()
                ->setGrow(3)
                ->setChild(padding()
                    ->setPaddings(18)
                    ->setChild(rounded()
                        ->setChild(activeExampleElement)))));

    Platform *platform = new Platform();
    platform->title = "Elementor examples";
    platform->size = {920, 640};
    platform->minSize = {640, 320};
    platform->application = application;

    platform->run();
}
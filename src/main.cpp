//
// Created by noartem on 14.04.2022.
//

#include "./library/Background.h"
#include "./library/Padding.h"
#include "./library/Application.h"
#include "./library/Platform.h"
#include "./library/Flex.h"
#include "./library/Flexible.h"
#include "./library/Sized.h"
#include "./library/Align.h"
#include "./library/Rounded.h"
#include "./library/Label.h"

using namespace elementor;

Element *makeExampleContainer(Element *child) {
    return background()
        ->setColor("#f1faee")
        ->setChild(padding()
            ->setPaddings(32)
            ->setChild(child));
}

Platform *makeExample(std::string description, Element *root, RenderSize size = {600, 840}) {
    Application *application = new Application();
    application->root = makeExampleContainer(root);

    Platform *platform = new Platform();
    platform->title = "Elementor example: " + description;
    platform->size = size;
    platform->minSize = size;
    platform->application = application;

    return platform;
}

void exampleMain() {
    Element *scene = background()
        ->setColor("#457b9d")
        ->setChild(padding()
            ->setPaddings(32)
            ->setChild(background()
                ->setColor("#a8dadc")
                ->setChild(padding()
                    ->setPaddings(64)
                    ->setChild(flex()
                        ->setSpacing(32)
                        ->appendChild(flexible()
                            ->setChild(background()
                                ->setColor("#e63946")))
                        ->appendChild(flexible()
                            ->setGrow(2)
                            ->setChild(flex()
                                ->setSpacing(24)
                                ->setDirection(FlexDirection::Column)
                                ->appendChild(flexible()
                                    ->setChild(background()
                                    ->setColor("#1d3557")))
                        ->appendChild(sized()
                            ->setSize(200)
                            ->setChild(background()
                                ->setColor("#1d3557")))))
                        ->appendChild(flexible()
                            ->setGrow(2)
                            ->setChild(background()
                                ->setColor("#e63946")))))));

    makeExample("Main", scene, {900, 600})->run();
}

void exampleFlexibleExpanedAndSized() {
    Element *scene = flex()
        ->setSpacing(24)
        ->setDirection(FlexDirection::Column)
        ->appendChild(flexible()
            ->setChild(flex()
                ->setSpacing(16)
                ->appendChild(flexible()
                    ->setChild(background()
                        ->setColor("#457B9D")))
                ->appendChild(flexible()
                    ->setChild(background()
                        ->setColor("#457B9D")))))
        ->appendChild(flexible()
            ->setChild(flex()
                ->setSpacing(16)
                ->appendChild(sized()
                    ->setSize(120)
                    ->setChild(background()
                        ->setColor("#457B9D")))
                ->appendChild(sized()
                    ->setSize(120)
                    ->setChild(background()
                        ->setColor("#457B9D")))))
        ->appendChild(flexible()
            ->setChild(flex()
                ->setSpacing(16)
                ->appendChild(flexible()
                    ->setChild(align()
                        ->setAlignment(Alignment::TopLeft)
                        ->setChild(sized()
                            ->setSize(120)
                            ->setChild(background()
                                ->setColor("#457B9D")))))
                ->appendChild(flexible()
                    ->setChild(align()
                        ->setAlignment(Alignment::TopLeft)
                        ->setChild(sized()
                            ->setSize(120)
                            ->setChild(background()
                                ->setColor("#457B9D")))))));

    makeExample("Flexible, Expanded and Sized", scene)->run();
}

Flexible *makeExampleFlexRow(FlexAlignment alignment, FlexCrossAlignment crossAlignment) {
    return flexible()
        ->setChild(flex()
            ->setSpacing(16)
            ->setAlignment(alignment)
            ->setCrossAlignment(crossAlignment)
            ->appendChild(sized()
                ->setSize(280, 200)
                ->setChild(background()
                    ->setColor("#457b9d")))
            ->appendChild(sized()
                ->setSize(200, 80)
                ->setChild(background()
                    ->setColor("#a8dadc"))));
}

void exampleFlexAlignment() {
    Element *scene = flex()
        ->setSpacing(24)
        ->setDirection(FlexDirection::Column)
        ->appendChild(makeExampleFlexRow(FlexAlignment::Start, FlexCrossAlignment::SpaceEvenly))
        ->appendChild(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceEvenly))
        ->appendChild(makeExampleFlexRow(FlexAlignment::End, FlexCrossAlignment::SpaceEvenly));

    makeExample("Flex alignment", scene)->run();
}

void exampleFlexCrossAlignment() {
    Element *scene = flex()
        ->setSpacing(24)
        ->setDirection(FlexDirection::Column)
        ->appendChild(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::Start))
        ->appendChild(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceEvenly))
        ->appendChild(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceBetween))
        ->appendChild(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::End));

    makeExample("Flex Cross Alignment", scene)->run();
}

Element *makeExampleAlign(Alignment alignment) {
    return flexible()
        ->setChild(background()
            ->setColor("a8dadc")
            ->setChild(align()
                ->setAlignment(alignment)
                ->setChild(sized()
                    ->setSize(40)
                    ->setChild(background()
                        ->setColor("#457b9d")))));
}

void exampleAlign() {
    Element *scene = flex()
        ->setSpacing(24)
        ->setDirection(FlexDirection::Column)
        ->appendChild(makeExampleAlign(Alignment::BottomCenter))
        ->appendChild(makeExampleAlign(Alignment::BottomLeft))
        ->appendChild(makeExampleAlign(Alignment::BottomRight))
        ->appendChild(makeExampleAlign(Alignment::Center))
        ->appendChild(makeExampleAlign(Alignment::CenterLeft))
        ->appendChild(makeExampleAlign(Alignment::CenterRight))
        ->appendChild(makeExampleAlign(Alignment::TopCenter))
        ->appendChild(makeExampleAlign(Alignment::TopLeft))
        ->appendChild(makeExampleAlign(Alignment::TopRight));

    makeExample("Align", scene)->run();
}

Element *makeExampleRounded(float radiusX, float radiusY) {
    return flexible()
        ->setChild(rounded()
            ->setRadius(radiusX, radiusY)
            ->setChild(background()
                ->setColor("#457b9d")
                ->setChild(padding()
                    ->setPaddings(24)
                    ->setChild(rounded()
                        ->setRadius(radiusX, radiusY)
                        ->setChild(background()
                            ->setColor("#a8dadc"))))));
}

void exampleRounded() {
    Element *scene = flex()
        ->setSpacing(24)
        ->appendChild(makeExampleRounded(10.0, 10.0))
        ->appendChild(makeExampleRounded(10.0, 20.0))
        ->appendChild(makeExampleRounded(20.0, 20.0))
        ->appendChild(makeExampleRounded(20.0, 30.0))
        ->appendChild(makeExampleRounded(30.0, 30.0))
        ->appendChild(makeExampleRounded(60.0, 120.0));

    makeExample("Rounded", scene, {720, 360})->run();
}

Element *makeButton(std::string text) {
    return flexible()
        ->setChild(align()
            ->setChild(sized()
                ->setSize(300, 100)
                ->setChild(rounded()
                    ->setRadius(8)
                    ->setChild(background()
                        ->setColor("#457b9d")
                        ->setChild(align()
                            ->setChild(label()
                                ->setFontColor("#ffffff")
                                ->setFontSize(24)
                                ->setText(text)))))));
}

void exampleLabel() {
    Element *scene = flex()
        ->setSpacing(24)
        ->setDirection(FlexDirection::Column)
        ->appendChild(makeButton("Text"))
        ->appendChild(makeButton("Apply"))
        ->appendChild(makeButton("Lorem Ipsum"))
        ->appendChild(makeButton("Some other text"))
        ->appendChild(makeButton("Click on me"));

    makeExample("Label", scene, {320, 640})->run();
}

int main(int argc, char *argv[]) {
    switch (atoi(argv[1])) {
        case 0:
            exampleMain();
            break;
        case 1:
            exampleFlexibleExpanedAndSized();
            break;
        case 2:
            exampleFlexAlignment();
            break;
        case 3:
            exampleFlexCrossAlignment();
            break;
        case 4:
            exampleAlign();
            break;
        case 5:
            exampleRounded();
            break;
        case 6:
            exampleLabel();
            break;
    }
}

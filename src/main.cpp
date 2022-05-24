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
#include "./library/Border.h"
#include "./library/Wrap.h"
#include "./library/Hoverable.h"
#include "./library/Clickable.h"
#include "./library/Scrollable.h"
#include "./library/Column.h"
#include "./library/Row.h"

using namespace elementor;

Platform *makeExample(std::string description, Element *root, Size size = {600, 840}) {
    Application *application = new Application();
    application->root = background()
        ->setColor("#ffffff")
        ->setChild(root);

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

Element *makeExampleAlign(Alignment alignment, std::string alignLabel) {
    return flexible()
        ->setChild(background()
            ->setColor("a8dadc")
            ->setChild(align()
                ->setAlignment(alignment)
                ->setChild(sized()
                    ->setSize(40)
                    ->setChild(background()
                        ->setColor("#457b9d")
                        ->setChild(align()
                            ->setChild(label()
                                ->setFontColor("#ffffff")
                                ->setFontSize(20)
                                ->setText(alignLabel)))))));
}

void exampleAlign() {
    Element *scene = flex()
        ->setSpacing(24)
        ->appendChild(flexible()
            ->setChild(flex()
                ->setSpacing(16)
                ->setDirection(FlexDirection::Column)
                ->appendChild(makeExampleAlign(Alignment::TopLeft, "TL"))
                ->appendChild(makeExampleAlign(Alignment::CenterLeft, "CL"))
                ->appendChild(makeExampleAlign(Alignment::BottomLeft, "BR"))))
        ->appendChild(flexible()
            ->setChild(flex()
                ->setSpacing(16)
                ->setDirection(FlexDirection::Column)
                ->appendChild(makeExampleAlign(Alignment::TopCenter, "TC"))
                ->appendChild(makeExampleAlign(Alignment::Center, "CC"))
                ->appendChild(makeExampleAlign(Alignment::BottomCenter, "BC"))))
        ->appendChild(flexible()
            ->setChild(flex()
                ->setSpacing(16)
                ->setDirection(FlexDirection::Column)
                ->appendChild(makeExampleAlign(Alignment::TopRight, "TR"))
                ->appendChild(makeExampleAlign(Alignment::CenterRight, "CR"))
                ->appendChild(makeExampleAlign(Alignment::BottomRight, "BR"))));

    makeExample("Align", scene, {480, 480})->run();
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
    return rounded()
        ->setRadius(16)
        ->setChild(background()
            ->setColor("#457b9d")
            ->setChild(border()
                ->setWidth(12)
                ->setColor("#a8dadc")
                ->setRadius(16)
                ->setChild(padding()
                    ->setPaddings(24, 36)
                    ->setChild(label()
                        ->setFontColor("#ffffff")
                        ->setFontSize(24)
                        ->setText(text)))));
}

Element *makeAlignedButton(std::string text) {
    return flexible()
        ->setChild(align()
            ->setChild(makeButton(text)));
}

void exampleLabel() {
    Element *scene = flex()
        ->setSpacing(24)
        ->setDirection(FlexDirection::Column)
        ->appendChild(makeAlignedButton("Text"))
        ->appendChild(makeAlignedButton("Apply"))
        ->appendChild(makeAlignedButton("Lorem Ipsum"))
        ->appendChild(makeAlignedButton("Some other text"))
        ->appendChild(makeAlignedButton("Click on me"));

    makeExample("Label", scene, {360, 640})->run();
}

void exampleWrap() {
    Element *scene = wrap()
        ->setSpacing(24, 12)
        ->appendChild(makeButton("Text"))
        ->appendChild(makeButton("Apply"))
        ->appendChild(makeButton("Lorem Ipsum"))
        ->appendChild(makeButton("Some other text"))
        ->appendChild(makeButton("Click on me"))
        ->appendChild(makeButton("Text"))
        ->appendChild(makeButton("Apply"))
        ->appendChild(makeButton("Lorem Ipsum"))
        ->appendChild(makeButton("Some other text"))
        ->appendChild(makeButton("Click on me"));

    makeExample("Wrap", scene, {360, 640})->run();
}

Element *makeHoverableButton(std::string text) {
    Background *buttonBackground = background();

    return hoverable()
        ->setChild(rounded()
            ->setRadius(16)
            ->setChild(buttonBackground
                ->setColor("#457b9d")
                ->setChild(border()
                    ->setWidth(12)
                    ->setColor("#a8dadc")
                    ->setRadius(16)
                    ->setChild(padding()
                        ->setPaddings(24, 36)
                        ->setChild(label()
                            ->setFontColor("#ffffff")
                            ->setFontSize(24)
                            ->setText(text))))))
        ->onEnter([buttonBackground]() { buttonBackground->setColor("#1d3557"); })
        ->onLeave([buttonBackground]() { buttonBackground->setColor("#457b9d"); });
}

void exampleHoverable() {
    Element *scene = wrap()
        ->setSpacing(24, 12)
        ->appendChild(makeHoverableButton("Text"))
        ->appendChild(makeHoverableButton("Apply"))
        ->appendChild(makeHoverableButton("Lorem Ipsum"))
        ->appendChild(makeHoverableButton("Some other text"))
        ->appendChild(makeHoverableButton("Click on me"));

    makeExample("Hoverable", scene, {360, 640})->run();
}

Element *makeClickableButton(std::string text, bool &active) {
    Background *buttonBackground = background();

    return hoverable()
        ->setChild(clickable()
            ->setChild(rounded()
                ->setRadius(16)
                ->setChild(buttonBackground
                    ->setColor("#457b9d")
                    ->setChild(border()
                        ->setWidth(12)
                        ->setColor("#a8dadc")
                        ->setRadius(16)
                        ->setChild(padding()
                            ->setPaddings(24, 36)
                            ->setChild(label()
                                ->setFontColor("#ffffff")
                                ->setFontSize(24)
                                ->setText(text))))))
            ->onClick([&active, buttonBackground] () mutable {
                active = !active;
                if (active) {
                    buttonBackground->setColor("#e63946");
                } else {
                    buttonBackground->setColor("#457b9d");
                }
            }))
        ->onEnter([&active, buttonBackground]() {
            if (active) {
                buttonBackground->setColor("#e63946");
            } else {
                buttonBackground->setColor("#1d3557");
            }
        })
        ->onLeave([&active, buttonBackground]() {
            if (active) {
                buttonBackground->setColor("#e2717a");
            } else {
                buttonBackground->setColor("#457b9d");
            }
        });
}

void exampleClickable() {
    bool firstActive;
    bool secondActive;
    bool thirdActive;
    bool fourthActive;

    Element *scene = wrap()
        ->setSpacing(24, 12)
        ->appendChild(makeClickableButton("Text", firstActive))
        ->appendChild(makeClickableButton("Apply", secondActive))
        ->appendChild(makeClickableButton("Lorem Ipsum", thirdActive))
        ->appendChild(makeClickableButton("Some other text", fourthActive));

    makeExample("Clickable", scene, {360, 640})->run();
}

Element *button(std::string text) {
    Background *buttonBackground = background();
    Element *button = rounded()
        ->setRadius(8)
        ->setChild(buttonBackground
            ->setColor("#0065FB")
            ->setChild(padding()
                ->setPaddings(16, 24)
                ->setChild(label()
                    ->setFontColor("#ffffff")
                    ->setFontSize(18)
                    ->setText(text))));

    return hoverable()
        ->setChild(button)
        ->onEnter([buttonBackground] () { buttonBackground->setColor("#005CE6"); })
        ->onLeave([buttonBackground] () { buttonBackground->setColor("#0065FB"); });
}

void exampleScroll() {
    Element *scene = align()
        ->setAlignment(Alignment::Center)
        ->setChild(scrollable()
            ->setChild(padding()
                ->setPaddings(12)
                ->setChild(column()
                    ->setSpacing(12)
                    ->setAlignment(ColumnAlignment::Center)
                    ->appendChild(button("Text"))
                    ->appendChild(button("Apply"))
                    ->appendChild(button("Lorem Ipsum"))
                    ->appendChild(button("Some other text"))
                    ->appendChild(button("Click on me"))
                    ->appendChild(button("Text"))
                    ->appendChild(button("Apply"))
                    ->appendChild(button("Lorem Ipsum"))
                    ->appendChild(button("Some other text"))
                    ->appendChild(button("Click on me"))
                    ->appendChild(button("Text"))
                    ->appendChild(button("Apply"))
                    ->appendChild(button("Lorem Ipsum"))
                    ->appendChild(button("Some other text"))
                    ->appendChild(button("Click on me")))));

    makeExample("Scroll", scene, {320, 360})->run();
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
        case 7:
            exampleWrap();
            break;
        case 8:
            exampleHoverable();
            break;
        case 9:
            exampleClickable();
            break;
        case 10:
            exampleScroll();
            break;
    }
}

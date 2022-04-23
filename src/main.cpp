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
#include "./library/Expanded.h"
#include "./library/Align.h"
#include "./library/Rounded.h"
#include "./library/Label.h"

using namespace elementor;

Element *makeExampleContainer(Element *child) {
    return new Background("#f1faee", new Padding(32, child));
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
    Background *jBackground = new Background("#e63946");
    Flexible *jElement = new Flexible(2, jBackground);
    Background *iColumnBox1Background = new Background("#1d3557");
    Flexible *iColumnBox1 = new Flexible(iColumnBox1Background);
    Background *iColumnBox2Background = new Background("#1d3557");
    Sized *iColumnBox2 = new Sized(140, iColumnBox2Background);
    Flex *iColumn = new Flex(24, FlexDirection::Column, {iColumnBox1, iColumnBox2});
    Flexible *iElement = new Flexible(2, iColumn);
    Background *hBackground = new Background("#e63946");
    Flexible *hElement = new Flexible(hBackground);
    Flex *gElement = new Flex(32, {hElement, iElement, jElement});
    Padding *fElement = new Padding(64, gElement);
    Background *eElement = new Background("#a8dadc", fElement);
    Padding *dElement = new Padding(32, eElement);
    Background *cElement = new Background("#457b9d", dElement);

    makeExample("Main", cElement, {900, 600})->run();
}

void exampleFlexibleExpanedAndSized() {
    Background *background = new Background("#457B9D");
    Flexible *flexible = new Flexible(background);
    Sized *sized = new Sized(200, background);
    Expanded *expanded = new Expanded(sized);
    Flex *rowWithFlexible = new Flex(24, {flexible, flexible});
    Flexible *rowWithFlexibleWrapper = new Flexible(rowWithFlexible);
    Flex *rowWithExpanded = new Flex(24, {expanded, expanded});
    Flexible *rowWithExpandedWrapper = new Flexible(rowWithExpanded);
    Flex *rowWithSized = new Flex(24, {sized, sized});
    Flexible *rowWithSizedWrapper = new Flexible(rowWithSized);
    Flex *examples = new Flex(24, FlexDirection::Column, {rowWithFlexibleWrapper, rowWithSizedWrapper, rowWithExpandedWrapper});

    makeExample("Flexible, Expanded and Sized", examples)->run();
}

Flexible* makeExampleFlexRow(FlexAlignment alignment, FlexCrossAlignment crossAlignment) {
    Background *box1Background = new Background("#457b9d");
    Sized *box1 = new Sized(280, 200, box1Background);
    Background *box2Background = new Background("#a8dadc");
    Sized *box2 = new Sized(200, 80, box2Background);
    Flex *row = new Flex(24, FlexDirection::Row, alignment, {box1, box2});
    Flexible *rowContainer = new Flexible(row);
    return rowContainer;
}

void exampleFlexAlignment() {
    Flex *examples = new Flex(24, FlexDirection::Column, {
        makeExampleFlexRow(FlexAlignment::Start, FlexCrossAlignment::SpaceEvenly),
        makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceEvenly),
        makeExampleFlexRow(FlexAlignment::End, FlexCrossAlignment::SpaceEvenly)
    });

    makeExample("Flex alignment", examples)->run();
}

void exampleFlexCrossAlignment() {
    Flex *examples = new Flex(24, FlexDirection::Column, {
        makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::Start),
        makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceEvenly),
        makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceBetween),
        makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::End),
    });

    makeExample("Flex Cross Alignment", examples)->run();
}

Element *makeExampleAlign(Alignment alignment) {
    Background *sizedBackground = new Background("#457b9d");
    Sized *sized = new Sized(40, sizedBackground);
    Align *align = new Align(alignment, sized);
    Background *alignBackground = new Background("#a8dadc", align);
    Flexible *alignContainer = new Flexible(alignBackground);
    return alignContainer;
}

void exampleAlign() {
    Flex *examples = new Flex(24, FlexDirection::Column, {
        makeExampleAlign(Alignment::BottomCenter),
        makeExampleAlign(Alignment::BottomLeft),
        makeExampleAlign(Alignment::BottomRight),
        makeExampleAlign(Alignment::Center),
        makeExampleAlign(Alignment::CenterLeft),
        makeExampleAlign(Alignment::CenterRight),
        makeExampleAlign(Alignment::TopCenter),
        makeExampleAlign(Alignment::TopLeft),
        makeExampleAlign(Alignment::TopRight),
    });

    makeExample("Align", examples)->run();
}

Element *makeExampleRounded(float radius) {
    Background *innerRoundedBackground = new Background("#a8dadc");
    Rounded *innerRounded = new Rounded(12, innerRoundedBackground);
    Padding *innerRoundedPadding = new Padding(24, innerRounded);
    Background *roundedBackground = new Background("#457b9d", innerRoundedPadding);
    Rounded *rounded = new Rounded(radius, roundedBackground);
    Flexible *roundedContainer = new Flexible(rounded);
    return roundedContainer;
}

void exampleRounded() {
    Flex *examples = new Flex(24, {
        makeExampleRounded(10),
        makeExampleRounded(20),
        makeExampleRounded(30),
        makeExampleRounded(40),
    });

    makeExample("Rounded", examples, {480, 240})->run();
}

Element *makeButton(std::string text) {
    Label *label = new Label(text, "#ffffff", 24);
    Align *labelAlign = new Align(Alignment::Center, label);
    Background *background = new Background("#457b9d", labelAlign);
    Rounded *rounded = new Rounded(8, background);
    Sized *sized = new Sized(300, 100, rounded);
    Align *align = new Align(Alignment::Center, sized);
    Expanded *expanded = new Expanded(align);
    return expanded;
}

void exampleLabel() {
    Flex *examples = new Flex(24, FlexDirection::Column, {
        makeButton("Text"),
        makeButton("Apply"),
        makeButton("Lorem Ipsum"),
        makeButton("Some other text"),
        makeButton("Click on me"),
    });

    makeExample("Label", examples, {320, 640})->run();
}

int main(int argc, char* argv[]) {
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

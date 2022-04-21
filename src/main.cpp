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

using namespace elementor;

Element *makeExampleContainer(Element *child) {
    Padding *containerPadding = new Padding();
    containerPadding->setPaddings(32);
    containerPadding->child = child;

    Background *container = new Background();
    container->setColor("#f1faee");
    container->child = containerPadding;

    return container;
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
    Background *jBackground = new Background();
    jBackground->setColor("#e63946");

    Flexible *jElement = new Flexible();
    jElement->grow = 2;
    jElement->child = jBackground;

    Background *iColumnBox1Background = new Background();
    iColumnBox1Background->setColor("#1d3557");

    Flexible *iColumnBox1 = new Flexible();
    iColumnBox1->child = iColumnBox1Background;

    Background *iColumnBox2Background = new Background();
    iColumnBox2Background->setColor("#1d3557");

    Sized *iColumnBox2 = new Sized();
    iColumnBox2->width = 140;
    iColumnBox2->height = 140;
    iColumnBox2->child = iColumnBox2Background;

    Flex *iColumn = new Flex();
    iColumn->spacing = 24;
    iColumn->direction = FlexDirection::Column;
    iColumn->children.push_back(iColumnBox1);
    iColumn->children.push_back(iColumnBox2);

    Flexible *iElement = new Flexible();
    iElement->grow = 2;
    iElement->child = iColumn;

    Background *hBackground = new Background();
    hBackground->setColor("#e63946");

    Flexible *hElement = new Flexible();
    hElement->child = hBackground;

    Flex *gElement = new Flex();
    gElement->spacing = 32;
    gElement->children.push_back(hElement);
    gElement->children.push_back(iElement);
    gElement->children.push_back(jElement);

    Padding *fElement = new Padding();
    fElement->setPaddings(64);
    fElement->child = gElement;

    Background *eElement = new Background();
    eElement->setColor("#a8dadc");
    eElement->child = fElement;

    Padding *dElement = new Padding();
    dElement->setPaddings(32);
    dElement->child = eElement;

    Background *cElement = new Background();
    cElement->setColor("#457b9d");
    cElement->child = dElement;

    makeExample("Main", cElement, {900, 600})->run();
}

void exampleFlexibleExpanedAndSized() {
    Background *background = new Background();
    background->setColor("#457B9D");

    Flexible *flexible = new Flexible();
    flexible->child = background;

    Sized *sized = new Sized();
    sized->width = 200;
    sized->height = 200;
    sized->child = background;

    Expanded *expanded = new Expanded();
    expanded->child = sized;

    Flex *rowWithFlexible = new Flex();
    rowWithFlexible->spacing = 24;
    rowWithFlexible->children.push_back(flexible);
    rowWithFlexible->children.push_back(flexible);

    Flexible *rowWithFlexibleWrapper = new Flexible();
    rowWithFlexibleWrapper->child = rowWithFlexible;

    Flex *rowWithExpanded = new Flex();
    rowWithExpanded->spacing = 24;
    rowWithExpanded->children.push_back(expanded);
    rowWithExpanded->children.push_back(expanded);

    Flexible *rowWithExpandedWrapper = new Flexible();
    rowWithExpandedWrapper->child = rowWithExpanded;

    Flex *rowWithSized = new Flex();
    rowWithSized->spacing = 24;
    rowWithSized->children.push_back(sized);
    rowWithSized->children.push_back(sized);

    Flexible *rowWithSizedWrapper = new Flexible();
    rowWithSizedWrapper->child = rowWithSized;

    Flex *examples = new Flex();
    examples->direction = FlexDirection::Column;
    examples->spacing = 24;
    examples->children.push_back(rowWithFlexibleWrapper);
    examples->children.push_back(rowWithSizedWrapper);
    examples->children.push_back(rowWithExpandedWrapper);

    makeExample("Flexible, Expanded and Sized", examples)->run();
}

Flexible* makeExampleFlexRow(FlexAlignment alignment, FlexCrossAlignment crossAlignment) {
    Background *box1Background = new Background();
    box1Background->setColor("#457b9d");

    Sized *box1 = new Sized();
    box1->width = 280;
    box1->height = 200;
    box1->child = box1Background;

    Background *box2Background = new Background();
    box2Background->setColor("#a8dadc");

    Sized *box2 = new Sized();
    box2->width = 200;
    box2->height = 80;
    box2->child = box2Background;

    Flex *row = new Flex();
    row->spacing = 24;
    row->direction = FlexDirection::Row;
    row->alignment = alignment;
    row->crossAlignment = crossAlignment;
    row->children.push_back(box1);
    row->children.push_back(box2);

    Flexible *rowContainer = new Flexible();
    rowContainer->child = row;

    return rowContainer;
}

void exampleFlexAlignment() {
    Flex *examples = new Flex();
    examples->direction = FlexDirection::Column;
    examples->spacing = 24;
    examples->children.push_back(makeExampleFlexRow(FlexAlignment::Start, FlexCrossAlignment::SpaceEvenly));
    examples->children.push_back(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceEvenly));
    examples->children.push_back(makeExampleFlexRow(FlexAlignment::End, FlexCrossAlignment::SpaceEvenly));

    makeExample("Flex alignment", examples)->run();
}

void exampleFlexCrossAlignment() {
    Flex *examples = new Flex();
    examples->direction = FlexDirection::Column;
    examples->spacing = 24;
    examples->children.push_back(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::Start));
    examples->children.push_back(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceEvenly));
    examples->children.push_back(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceBetween));
    examples->children.push_back(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::End));

    makeExample("Flex Cross Alignment", examples)->run();
}

Element *makeExampleAlign(Alignment alignment) {
    Background *sizedBackground = new Background();
    sizedBackground->setColor("#457b9d");

    Sized *sized = new Sized();
    sized->width = 40;
    sized->height = 40;
    sized->child = sizedBackground;

    Align *align = new Align();
    align->setAlignment(alignment);
    align->child = sized;

    Background *alignBackground = new Background();
    alignBackground->setColor("#a8dadc");
    alignBackground->child = align;

    Flexible *alignContainer = new Flexible();
    alignContainer->child = alignBackground;

    return alignContainer;
}

void exampleAlign() {
    Flex *examples = new Flex();
    examples->direction = FlexDirection::Column;
    examples->spacing = 24;
    examples->children.push_back(makeExampleAlign(Alignment::BottomCenter));
    examples->children.push_back(makeExampleAlign(Alignment::BottomLeft));
    examples->children.push_back(makeExampleAlign(Alignment::BottomRight));
    examples->children.push_back(makeExampleAlign(Alignment::Center));
    examples->children.push_back(makeExampleAlign(Alignment::CenterLeft));
    examples->children.push_back(makeExampleAlign(Alignment::CenterRight));
    examples->children.push_back(makeExampleAlign(Alignment::TopCenter));
    examples->children.push_back(makeExampleAlign(Alignment::TopLeft));
    examples->children.push_back(makeExampleAlign(Alignment::TopRight));

    makeExample("Align", examples)->run();
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
    }
}

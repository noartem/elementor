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

using namespace elementor;

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

    Padding *bElement = new Padding();
    bElement->setPaddings(48);
    bElement->child = cElement;

    Background *aElement = new Background();
    aElement->setColor("#f1faee");
    aElement->child = bElement;

    Application *application = new Application();
    application->root = aElement;

    Platform *platform = new Platform();
    platform->title = "Elementor example";
    platform->size = {900, 600};
    platform->minSize = {720, 480};
    platform->maxSize = {1440, 960};
    platform->application = application;

    platform->run();
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

    Flex *rowsColumn = new Flex();
    rowsColumn->direction = FlexDirection::Column;
    rowsColumn->spacing = 32;
    rowsColumn->children.push_back(rowWithFlexibleWrapper);
    rowsColumn->children.push_back(rowWithSizedWrapper);
    rowsColumn->children.push_back(rowWithExpandedWrapper);

    Padding *containerPadding = new Padding();
    containerPadding->setPaddings(48);
    containerPadding->child = rowsColumn;

    Background *container = new Background();
    container->setColor("#f1faee");
    container->child = containerPadding;

    Application *application = new Application();
    application->root = container;

    Platform *platform = new Platform();
    platform->title = "Elementor example: flexible, expanded and sized";
    platform->size = {840, 600};
    platform->minSize = {840, 600};
    platform->application = application;

    platform->run();
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
    Flex *rowsColumn = new Flex();
    rowsColumn->direction = FlexDirection::Column;
    rowsColumn->spacing = 24;
    rowsColumn->children.push_back(makeExampleFlexRow(FlexAlignment::Start, FlexCrossAlignment::SpaceEvenly));
    rowsColumn->children.push_back(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceEvenly));
    rowsColumn->children.push_back(makeExampleFlexRow(FlexAlignment::End, FlexCrossAlignment::SpaceEvenly));

    Padding *containerPadding = new Padding();
    containerPadding->setPaddings(32);
    containerPadding->child = rowsColumn;

    Background *container = new Background();
    container->setColor("#f1faee");
    container->child = containerPadding;

    Application *application = new Application();
    application->root = container;

    Platform *platform = new Platform();
    platform->title = "Elementor example: flex alignment";
    platform->size = {840, 600};
    platform->minSize = {840, 600};
    platform->application = application;

    platform->run();
}

void exampleFlexCrossAlignment() {
    Flex *rowsColumn = new Flex();
    rowsColumn->direction = FlexDirection::Column;
    rowsColumn->spacing = 24;
    rowsColumn->children.push_back(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::Start));
    rowsColumn->children.push_back(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceEvenly));
    rowsColumn->children.push_back(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::SpaceBetween));
    rowsColumn->children.push_back(makeExampleFlexRow(FlexAlignment::Center, FlexCrossAlignment::End));

    Padding *containerPadding = new Padding();
    containerPadding->setPaddings(32);
    containerPadding->child = rowsColumn;

    Background *container = new Background();
    container->setColor("#f1faee");
    container->child = containerPadding;

    Application *application = new Application();
    application->root = container;

    Platform *platform = new Platform();
    platform->title = "Elementor example: flex cross alignment";
    platform->size = {840, 600};
    platform->minSize = {840, 600};
    platform->application = application;

    platform->run();
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
    }
}

//
// Created by noartem on 14.04.2022.
//

#include "./library/Background.h"
#include "./library/Padding.h"
#include "./library/Application.h"
#include "./library/Platform.h"
#include "./library/Flex.h"

using namespace elementor;

int main(void) {
    Background *lElement = new Background();
    lElement->setColor("#1d3557");

    Background *kElement = new Background();
    kElement->setColor("#1d3557");

    Background *jElement = new Background();
    jElement->setColor("#e63946");

    Flex *iElement = new Flex();
    iElement->gap = 24;
    iElement->direction = FlexDirection::Column;
    iElement->children.push_back(lElement);
    iElement->children.push_back(kElement);
    iElement->children.push_back(jElement);

    Background *hElement = new Background();
    hElement->setColor("#e63946");

    Flex *gElement = new Flex();
    gElement->gap = 32;
    gElement->children.push_back(hElement);
    gElement->children.push_back(iElement);

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
    platform->title = "Elementor Test";
    platform->size = {720, 480};
    platform->minSize = {640, 427};
    platform->maxSize = {1440, 960};
    platform->application = application;

    platform->run();
}
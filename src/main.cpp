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

using namespace elementor;

int main(void) {
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
    platform->title = "Elementor Test";
    platform->size = {720, 480};
    platform->minSize = {640, 427};
    platform->maxSize = {1440, 960};
    platform->application = application;

    platform->run();
}
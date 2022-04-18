//
// Created by noartem on 14.04.2022.
//

#include "./library/Background.h"
#include "./library/Padding.h"
#include "./library/Application.h"
#include "./library/Platform.h"

using namespace elementor;

int main(void) {
    Background *gElement = new Background();
    gElement->setColor("#FF9F1C");

    Padding *fElement = new Padding();
    fElement->setPaddings(64);
    fElement->child = gElement;

    Background *eElement = new Background();
    eElement->setColor("#CBF3F0");
    eElement->child = fElement;

    Padding *dElement = new Padding();
    dElement->setPaddings(32);
    dElement->child = eElement;

    Background *cElement = new Background();
    cElement->setColor("#2EC4B6");
    cElement->child = dElement;

    Padding *bElement = new Padding();
    bElement->setPaddings(48);
    bElement->child = cElement;

    Background *aElement = new Background();
    aElement->color = SK_ColorWHITE;
    aElement->child = bElement;

    Application *application = new Application();
    application->root = aElement;

    Platform *platform = new Platform();
    platform->title = "Elementor Test";
    platform->size = {720, 480};
    platform->minSize = {480, 320};
    platform->maxSize = {1440, 960};
    platform->application = application;

    platform->run();
}
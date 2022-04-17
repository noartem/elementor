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
    gElement->color = SkColorSetARGB(0xFF, 0xFF, 0x9F, 0x1C);

    Padding *fElement = new Padding();
    fElement->setPaddings(64);
    fElement->child = gElement;

    Background *eElement = new Background();
    eElement->color = SkColorSetARGB(0xFF, 0xCB, 0xF3, 0xF0);
    eElement->child = fElement;

    Padding *dElement = new Padding();
    dElement->setPaddings(32);
    dElement->child = eElement;

    Background *cElement = new Background();
    cElement->color = SkColorSetARGB(0xFF, 0x2E, 0xC4, 0xB6);
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
    platform->width = 720;
    platform->height = 480;
    platform->application = application;

    platform->run();
}
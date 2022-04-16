//
// Created by noartem on 14.04.2022.
//

#include "./library/Background.h"
#include "./library/Padding.h"
#include "./library/Application.h"
#include "./library/Platform.h"

int main(void) {
    elementor::Background rootElement;
    rootElement.color = SK_ColorWHITE;

    elementor::Padding paddingElement;
    paddingElement.setPaddings(32);
    rootElement.child = &paddingElement;

    elementor::Background childElement;
    childElement.color = SK_ColorBLACK;
    paddingElement.child = &childElement;

    elementor::Application application;
    application.root = &rootElement;

    elementor::Platform platform;
    platform.title = "Elementor Test";
    platform.width = 400;
    platform.height = 400;
    platform.application = application;

    platform.run();
}
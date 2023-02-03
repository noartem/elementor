//
// Created by noartem on 03.02.2023.
//

#include "ExampleButton.h"
#include "components/Scroll.h"
#include "components/Button.h"

std::string ExampleButton::getName() {
    return "Button";
}

std::string ExampleButton::getDescription() {
    return "Just click on it!";
}

Element *buttonBasicExample() {
    auto buttonElement = new Button();
    const std::string unClickedText = "Click on me...";
    const std::string clickedText = "Clicked!";

    return buttonElement
        ->setLabel(unClickedText)
        ->onClick([buttonElement, unClickedText, clickedText]() {
            buttonElement->setLabel(buttonElement->getLabel() == clickedText ? unClickedText : clickedText);
        });
}

Element *buttonColorsExample() {
    auto buttonElement = new Button();

    return hoverable()
        ->setChild(buttonElement
            ->setLabel("Click on me")
            ->setBackgroundColor("#4E8752")
            ->setTextColor("#FFFFFF")
            ->onClick([buttonElement]() {
                buttonElement->setLabel(buttonElement->getLabel() + "!");
            }))
        ->onEnter([buttonElement]() {
            buttonElement->setBackgroundColor("#4E8752");
        })
        ->onLeave([buttonElement]() {
            buttonElement->setBackgroundColor("#57965C");
        });
}

Element *ExampleButton::getScene(ApplicationContext *ctx) {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(24)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Basic"))
                ->appendChild(alignWidth()
                    ->setChild(buttonBasicExample()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("With custom colors"))
                ->appendChild(alignWidth()
                    ->setChild(buttonColorsExample()))));
}

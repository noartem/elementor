//
// Created by noartem on 25.08.2022.
//

#include "ExampleTextInput.h"
#include "components/Scroll.h"
#include "components/TextInput.h"

std::string ExampleTextInput::getName() {
    return "Text Input";
}

std::string ExampleTextInput::getDescription() {
    return "Simple text input field";
}

Element *ExampleTextInput::getScene(ApplicationContext *ctx) {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(24)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Basic"))
                ->appendChild(textInput())));
}

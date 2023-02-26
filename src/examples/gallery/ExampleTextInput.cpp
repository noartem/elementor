//
// Created by noartem on 25.08.2022.
//

#include "ExampleTextInput.h"

std::string ExampleTextInput::getName() {
    return "Text Input";
}

std::string ExampleTextInput::getDescription() {
    return "Simple text input field";
}

std::shared_ptr<Element> ExampleTextInput::getScene(std::shared_ptr<ApplicationContext> ctx) {
    auto tp = timePicker();
    auto tpResult = text();

    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(24)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Basic"))
                ->appendChild(textInput())
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Time picker"))
                ->appendChild(column()
                    ->setSpacing(8)
                    ->appendChild(tp
                        ->onInput([tp, tpResult]() {
                            char buffer[256];
                            strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", &tp->getTime());
                            tpResult->setText("Result: " + std::string(buffer));
                        }))
                    ->appendChild(tpResult
                        ->setFontColor("#062016")
                        ->setFontSize(14)
                        ->setText("Result: ")))
                ->appendChild(timePicker()
                    ->setTemplate("D.M.Y"))));
}

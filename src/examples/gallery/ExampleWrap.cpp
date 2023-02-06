//
// Created by noartem on 02.06.2022.
//

#include "ExampleWrap.h"

std::string ExampleWrap::getName() {
    return "Wrap";
}

std::string ExampleWrap::getDescription() {
    return "Row/Column wich wrap children to new line if overflow";
}

std::shared_ptr<Element> exampleWrapRow() {
    std::shared_ptr<Wrap> wrapElement = wrap()
        ->setSpacing(8)
        ->setCrossSpacing(12);

    for (int i = 0; i < 15; i++) {
        wrapElement->appendChild(boxSized(i % 2 == 0 ? "#BEE8FA" : "#CDE8D9", randInRange(64, 256), 48));
    }

    return wrapElement;
}

std::shared_ptr<Element> exampleWrapColumn() {
    std::shared_ptr<Wrap> wrapElement = wrap()
        ->setSpacing(8)
        ->setCrossSpacing(12)
        ->setDirection(WrapDirection::Column);

    for (int i = 0; i < 25; i++) {
        wrapElement->appendChild(boxSized(i % 2 == 0 ? "#BEE8FA" : "#CDE8D9", 48, randInRange(64, 128)));
    }

    return wrapElement;
}

std::shared_ptr<Element> ExampleWrap::getScene(std::shared_ptr<ApplicationContext> ctx) {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(48)
                ->appendChild(column()
                    ->setSpacing(6)
                    ->appendChild(text()
                        ->setFontColor("#062016")
                        ->setFontSize(16)
                        ->setText("Wrap row"))
                    ->appendChild(exampleWrapRow()))
                ->appendChild(column()
                    ->setSpacing(6)
                    ->appendChild(text()
                        ->setFontColor("#062016")
                        ->setFontSize(16)
                        ->setText("Wrap column"))
                    ->appendChild(height()
                        ->setHeight(384)
                        ->setChild(exampleWrapColumn())))));
}
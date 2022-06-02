//
// Created by noartem on 02.06.2022.
//

#include "ExampleWrap.h"
#include "Scroll.h"

std::string ExampleWrap::getName() {
    return "Wrap";
}

std::string ExampleWrap::getDescription() {
    return "Row/Column wich wrap children to new line if overflow";
}

Element *exampleWrapRow() {
    Wrap *wrapElement = wrap()
        ->setSpacing(8)
        ->setCrossSpacing(12);

    for (int i = 0; i < 15; i++) {
        wrapElement->appendChild(boxSized(i % 2 == 0 ? "#BEE8FA" : "#CDE8D9", randInRange(64, 256), 48));
    }

    return wrapElement;
}

Element *exampleWrapColumn() {
    Wrap *wrapElement = wrap()
        ->setSpacing(8)
        ->setCrossSpacing(12)
        ->setDirection(WrapDirection::Column);

    for (int i = 0; i < 25; i++) {
        wrapElement->appendChild(boxSized(i % 2 == 0 ? "#BEE8FA" : "#CDE8D9", 48, randInRange(64, 128)));
    }

    return wrapElement;
}

Element *ExampleWrap::getScene() {
    return scroll()
        ->setChild(padding()
            ->setPaddings(12, 18)
            ->setChild(column()
                ->setSpacing(48)
                ->appendChild(column()
                    ->setSpacing(6)
                    ->appendChild(label()
                        ->setFontColor("#062016")
                        ->setFontSize(16)
                        ->setText("Wrap row"))
                    ->appendChild(exampleWrapRow()))
                ->appendChild(column()
                    ->setSpacing(6)
                    ->appendChild(label()
                        ->setFontColor("#062016")
                        ->setFontSize(16)
                        ->setText("Wrap column"))
                    ->appendChild(height()
                        ->setHeight(384)
                        ->setChild(exampleWrapColumn())))));
}
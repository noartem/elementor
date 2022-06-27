//
// Created by noartem on 18.06.2022.
//

#include "ExampleSized.h"
#include "Scroll.h"

std::string ExampleSized::getName() {
    return "Sized";
}

std::string ExampleSized::getDescription() {
    return "Apply elemnts to strict height, width";
}

Element *exampleHeight() {
    return flex()
        ->setSpacing(12)
        ->appendChild(flexible()
            ->setChild(height()
                ->setHeight(64)
                ->setChild(box("#CDE8D9"))))
        ->appendChild(flexible()
            ->setChild(height()
                ->setHeight(128)
                ->setChild(box("#BEE8FA"))))
        ->appendChild(flexible()
            ->setChild(height()
                ->setHeight(48)
                ->setChild(box("#CDE8D9"))));
}

Element *exampleWidth() {
    return height()
        ->setHeight(256)
        ->setChild(flex()
            ->setDirection(FlexDirection::Column)
            ->setSpacing(12)
            ->appendChild(flexible()
                ->setChild(alignWidth()
                    ->setChild(width()
                        ->setWidth(128)
                        ->setChild(box("#CDE8D9")))))
            ->appendChild(flexible()
                ->setChild(alignWidth()
                    ->setChild(width()
                        ->setWidth(256)
                        ->setChild(box("#BEE8FA")))))
            ->appendChild(flexible()
                ->setChild(alignWidth()
                    ->setChild(width()
                        ->setWidth(192)
                        ->setChild(box("#CDE8D9"))))));
}

Element *exampleHeightAndWidth() {
    return column()
        ->setSpacing(12)
        ->appendChild(height()
            ->setHeight(128)
            ->setChild(width()
                ->setWidth(64)
                ->setChild(box("#CDE8D9"))))
        ->appendChild(height()
            ->setHeight(64)
            ->setChild(width()
                ->setWidth(128)
                ->setChild(box("#BEE8FA"))))
        ->appendChild(height()
            ->setHeight(192)
            ->setChild(width()
                ->setWidth(128)
                ->setChild(box("#CDE8D9"))));
}

Element *ExampleSized::getScene() {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(12)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Height"))
                ->appendChild(padding()
                    ->setPaddings(0, 16)
                    ->setChild(exampleHeight()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Width"))
                ->appendChild(padding()
                    ->setPaddings(0, 16)
                    ->setChild(exampleWidth()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Height and Width"))
                ->appendChild(padding()
                    ->setPaddings(0, 16)
                    ->setChild(exampleHeightAndWidth()))));
}

//
// Created by noartem on 29.05.2022.
//

#include "ExampleFlexChildren.h"

std::string ExampleFlexChildren::getName() {
    return "Flex children";
}

std::string ExampleFlexChildren::getDescription() {
    return "Flex children can be flexible or sized";
}

Element *box(std::string color) {
    return rounded()
        ->setRadius(8)
        ->setChild(background()
            ->setColor(color));
}

Element *ExampleFlexChildren::getScene() {
    return padding()
        ->setPaddings(12, 18)
        ->setChild(flex()
            ->setSpacing(12)
            ->setDirection(FlexDirection::Column)
            ->appendChild(flexible()
                ->setChild(flex()
                    ->setSpacing(8)
                    ->appendChild(flexible()
                        ->setChild(box("#CDE8D9")))
                    ->appendChild(flexible()
                        ->setGrow(4)
                        ->setChild(box("#CDE8D9")))
                    ->appendChild(flexible()
                        ->setGrow(2)
                        ->setChild(box("#CDE8D9")))))
            ->appendChild(flexible()
                ->setChild(flex()
                    ->setSpacing(8)
                    ->appendChild(width()
                        ->setWidth(128)
                        ->setChild(box("#BEE8FA")))
                    ->appendChild(width()
                        ->setWidth(128)
                        ->setChild(box("#BEE8FA")))
                    ->appendChild(width()
                        ->setWidth(256)
                        ->setChild(box("#BEE8FA")))))
            ->appendChild(flexible()
                ->setChild(flex()
                    ->setSpacing(8)
                    ->appendChild(width()
                        ->setWidth(160)
                        ->setChild(box("#BEE8FA")))
                    ->appendChild(flexible()
                        ->setChild(box("#CDE8D9")))))
            ->appendChild(flexible()
                ->setChild(flex()
                    ->setSpacing(8)
                    ->appendChild(flexible()
                        ->setChild(box("#CDE8D9")))
                    ->appendChild(width()
                        ->setWidth(128)
                        ->setChild(box("#BEE8FA")))
                    ->appendChild(flexible()
                        ->setGrow(2)
                        ->setChild(box("#CDE8D9")))
                    ->appendChild(width()
                        ->setWidth(96)
                        ->setChild(box("#BEE8FA")))))
            ->appendChild(flexible()
                ->setChild(flex()
                    ->setSpacing(8)
                    ->appendChild(width()
                        ->setWidth(128)
                        ->setChild(box("#BEE8FA")))
                    ->appendChild(flexible()
                        ->setGrow(2)
                        ->setChild(box("#CDE8D9")))
                    ->appendChild(width()
                        ->setWidth(96)
                        ->setChild(box("#BEE8FA"))))));
}

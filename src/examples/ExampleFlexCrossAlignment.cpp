//
// Created by noartem on 29.05.2022.
//

#include "ExampleFlexCrossAlignment.h"

std::string ExampleFlexCrossAlignment::getName() {
    return "Flex cross alignment";
}

std::string ExampleFlexCrossAlignment::getDescription() {
    return "Flex children can be aligned by cross axis";
}

Element *exampleCrossAlignment(FlexCrossAlignment crossAlignment) {
    return flex()
        ->setSpacing(8)
        ->setCrossAlignment(crossAlignment)
        ->appendChild(width()
            ->setWidth(128)
            ->setChild(height()
                ->setHeight(96)
                ->setChild(rounded()
                    ->setRadius(8)
                    ->setChild(background()
                        ->setColor("#CDE8D9")))))
        ->appendChild(width()
            ->setWidth(128)
            ->setChild(height()
                ->setHeight(192)
                ->setChild(rounded()
                    ->setRadius(8)
                    ->setChild(background()
                        ->setColor("#BEE8FA")))))
        ->appendChild(width()
            ->setWidth(96)
            ->setChild(height()
                ->setHeight(128)
                ->setChild(rounded()
                    ->setRadius(8)
                    ->setChild(background()
                        ->setColor("#CDE8D9")))));
}

Element *ExampleFlexCrossAlignment::getScene() {
    return padding()
        ->setPaddings(12, 18)
        ->setChild(flex()
            ->setSpacing(12)
            ->setDirection(FlexDirection::Column)
            ->appendChild(flexible()
                ->setChild(exampleCrossAlignment(FlexCrossAlignment::Start)))
            ->appendChild(flexible()
                ->setChild(exampleCrossAlignment(FlexCrossAlignment::Center)))
            ->appendChild(flexible()
                ->setChild(exampleCrossAlignment(FlexCrossAlignment::End)))
            ->appendChild(flexible()
                ->setChild(exampleCrossAlignment(FlexCrossAlignment::SpaceBetween)))
            ->appendChild(flexible()
                ->setChild(exampleCrossAlignment(FlexCrossAlignment::SpaceEvenly))));
}

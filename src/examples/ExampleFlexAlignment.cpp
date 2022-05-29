//
// Created by noartem on 29.05.2022.
//

#include "ExampleFlexAlignment.h"

std::string ExampleFlexAlignment::getName() {
    return "Flex alignment";
}

std::string ExampleFlexAlignment::getDescription() {
    return "Flex children can be aligned by main axis";
}

Element *exampleAlignment(FlexAlignment alignment) {
    return height()
        ->setHeight(192)
        ->setChild(flex()
            ->setSpacing(8)
            ->setAlignment(alignment)
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
                            ->setColor("#CDE8D9"))))));
}

Element *ExampleFlexAlignment::getScene() {
    return column()
        ->setSpacing(12)
        ->appendChild(exampleAlignment(FlexAlignment::Start))
        ->appendChild(exampleAlignment(FlexAlignment::Center))
        ->appendChild(exampleAlignment(FlexAlignment::End));
}

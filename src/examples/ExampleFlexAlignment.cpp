//
// Created by noartem on 29.05.2022.
//

#include "ExampleFlexAlignment.h"

std::string ExampleFlexAlignment::getName() {
    return "Flex alignment";
}

std::string ExampleFlexAlignment::getDescription() {
    return "Flex children can be aligned by two axis";
}

Element *makeRow(FlexAlignment alignment, FlexCrossAlignment crossAlignment) {
    return flexible()
        ->setChild(flex()
            ->setSpacing(16)
            ->setAlignment(alignment)
            ->setCrossAlignment(crossAlignment)
            ->appendChild(sized()
                ->setSize(280, 200)
                ->setChild(background()
                    ->setColor("#457b9d")))
            ->appendChild(sized()
                ->setSize(200, 80)
                ->setChild(background()
                    ->setColor("#a8dadc"))));
}

Element *ExampleFlexAlignment::getScene() {
    return flex()
        ->setSpacing(24)
        ->setDirection(FlexDirection::Column)
        ->appendChild(makeRow(FlexAlignment::Start, FlexCrossAlignment::SpaceEvenly))
        ->appendChild(makeRow(FlexAlignment::Center, FlexCrossAlignment::SpaceEvenly))
        ->appendChild(makeRow(FlexAlignment::End, FlexCrossAlignment::SpaceEvenly));
}

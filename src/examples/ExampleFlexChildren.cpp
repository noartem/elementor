//
// Created by noartem on 29.05.2022.
//

#include "ExampleFlexChildren.h"

std::string ExampleFlexChildren::getName() {
    return "Flex children";
}

std::string ExampleFlexChildren::getDescription() {
    return "Flex children can be Flexible, Expanded or Sized (by default)";
}

Element *ExampleFlexChildren::getScene() {
    return flex()
        ->setSpacing(24)
        ->setDirection(FlexDirection::Column)
        ->appendChild(flexible()
            ->setChild(flex()
                ->setSpacing(16)
                ->appendChild(flexible()
                    ->setChild(background()
                        ->setColor("#457B9D")))
                ->appendChild(flexible()
                    ->setChild(background()
                        ->setColor("#457B9D")))))
        ->appendChild(flexible()
            ->setChild(flex()
                ->setSpacing(16)
                ->appendChild(sized()
                    ->setSize(120)
                    ->setChild(background()
                        ->setColor("#457B9D")))
                ->appendChild(sized()
                    ->setSize(120)
                    ->setChild(background()
                        ->setColor("#457B9D")))))
        ->appendChild(flexible()
            ->setChild(flex()
                ->setSpacing(16)
                ->appendChild(flexible()
                    ->setChild(align()
                        ->setAlignment(Alignment::TopLeft)
                        ->setChild(sized()
                            ->setSize(120)
                            ->setChild(background()
                                ->setColor("#457B9D")))))
                ->appendChild(flexible()
                    ->setChild(align()
                        ->setAlignment(Alignment::TopLeft)
                        ->setChild(sized()
                            ->setSize(120)
                            ->setChild(background()
                                ->setColor("#457B9D")))))));
}

//
// Created by noartem on 03.02.2023.
//

#include "ExampleStack.h"

std::string ExampleStack::getName() {
    return "Stack";
}

std::string ExampleStack::getDescription() {
    return "Stack elements one on top of another";
}

Element *stackBasicExample() {
    return width()
        ->setWidth(512)
        ->setChild(height()
            ->setHeight(512)
            ->setChild(stack()
                ->appendChild(center()
                    ->setChild(boxSized("#EDF5F0", 512, 512)))
                ->appendChild(center()
                    ->setChild(boxSized("#CDE8D9", 512, 256)))
                ->appendChild(center()
                    ->setChild(boxSized("#BEE8FA", 128, 192)))
                ->appendChild(center()
                    ->setChild(boxSized("#DEEDE6", 256, 64)))
                ->appendChild(center()
                    ->setChild(rounded()
                        ->setRadius(8)
                        ->setChild(background()
                            ->setColor("#57965C")
                            ->setChild(padding()
                                ->setPaddings(32)
                                ->setChild(text()
                                    ->setFontColor("#FFFFFF")
                                    ->setFontSize(24)
                                    ->setText("Stack child"))))))
                ->appendChild(padding()
                    ->setPaddings(32, 64)
                    ->setChild(rounded()
                        ->setRadius(8)
                        ->setChild(background()
                            ->setColor("#366ACE")
                            ->setChild(padding()
                                ->setPaddings(6, 12, 10, 12)
                                ->setChild(text()
                                    ->setFontColor("#FFFFFF")
                                    ->setFontSize(12)
                                    ->setText("Positioned by padding"))))))));
}

std::string tooltipPlacementToString(TooltipPlacement placement) {
    switch (placement) {
        case TooltipPlacement::TopStart:
            return "TopStart";
        case TooltipPlacement::Top:
            return "Top";
        case TooltipPlacement::TopEnd:
            return "TopEnd";
        case TooltipPlacement::RightStart:
            return "RightStart";
        case TooltipPlacement::Right:
            return "Right";
        case TooltipPlacement::RightEnd:
            return "RightEnd";
        case TooltipPlacement::BottomStart:
            return "BottomStart";
        case TooltipPlacement::Bottom:
            return "Bottom";
        case TooltipPlacement::BottomEnd:
            return "BottomEnd";
        case TooltipPlacement::LeftStart:
            return "LeftStart";
        case TooltipPlacement::Left:
            return "Left";
        case TooltipPlacement::LeftEnd:
            return "LeftEnd";
    }
}

Element *tooltipPlacementExample(TooltipPlacement placement) {
    Tooltip *tooltipElement = tooltip();
    Background *backgroundElement = background();
    return padding()
        ->setPaddings(64)
        ->setChild(tooltipElement
            ->setPlacement(placement)
            ->setChild(hoverable()
                ->setChild(rounded()
                    ->setRadius(8)
                    ->setChild(width()
                        ->setWidth(192)
                        ->setChild(height()
                            ->setHeight(128)
                            ->setChild(backgroundElement
                                ->setColor("#DEEDE6")
                                ->setChild(padding()
                                    ->setPaddings(6, 12, 10, 12)
                                    ->setChild(center()
                                        ->setChild(text()
                                            ->setFontColor("#006C4C")
                                            ->setFontSize(12)
                                            ->setText(tooltipPlacementToString(placement)))))))))
                ->onEnter([tooltipElement, backgroundElement]() {
                    tooltipElement->setActive(true);
                    backgroundElement->setColor("#C2DDD3");
                })
                ->onLeave([tooltipElement, backgroundElement]() {
                    tooltipElement->setActive(false);
                    backgroundElement->setColor("#DEEDE6");
                }))
            ->setTip(rounded()
                ->setRadius(8)
                ->setChild(background()
                    ->setColor("#366ACE")
                    ->setChild(padding()
                        ->setPaddings(6, 12, 10, 12)
                        ->setChild(column()
                            ->setSpacing(4)
                            ->appendChild(text()
                                ->setFontColor("#FFFFFF")
                                ->setFontSize(12)
                                ->setText("Tooltip")))))));
}

Element *tooltipExample() {
    auto examples = column()
        ->setSpacing(8);

    std::vector<std::vector<TooltipPlacement>> placementGroups = {{TooltipPlacement::TopStart, TooltipPlacement::Top, TooltipPlacement::TopEnd},
                                                                  {TooltipPlacement::RightStart, TooltipPlacement::Right, TooltipPlacement::RightEnd},
                                                                  {TooltipPlacement::BottomStart, TooltipPlacement::Bottom, TooltipPlacement::BottomEnd},
                                                                  {TooltipPlacement::LeftStart, TooltipPlacement::Left, TooltipPlacement::LeftEnd}};

    for (const auto& placementGroup : placementGroups) {
        auto groupExamples = row()
            ->setSpacing(8);

        for (auto placement : placementGroup) {
            groupExamples->appendChild(tooltipPlacementExample(placement));
        }

        examples->appendChild(groupExamples);
    }

    return examples;
}

Element *comboxExample() {
    return combox()
        ->setPlaceholder("Select an option")
        ->addOption("1", "Option 1")
        ->addOption("2", "Option 2")
        ->addOption("3", "Option 3")
        ->addOption("4", "Option 4")
        ->addOption("5", "Option 5")
        ->addOption("6", "Option 6")
        ->addOption("7", "Option 7")
        ->addOption("8", "Option 8")
        ->addOption("9", "Option 9")
        ->addOption("10", "Option 10")
        ->addOption("11", "Option 11")
        ->addOption("12", "Option 12")
        ->addOption("13", "Option 13")
        ->addOption("14", "Option 14")
        ->addOption("15", "Option 15")
        ->addOption("16", "Option 16")
        ->addOption("17", "Option 17")
        ->addOption("18", "Option 18")
        ->addOption("19", "Option 19")
        ->addOption("20", "Option 20");
}

Element *ExampleStack::getScene(ApplicationContext *ctx) {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(24)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Combox"))
                ->appendChild(alignWidth()
                    ->setChild(comboxExample()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Tooltip"))
                ->appendChild(alignWidth()
                    ->setChild(tooltipExample()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Basic"))
                ->appendChild(alignWidth()
                    ->setChild(stackBasicExample()))));
}

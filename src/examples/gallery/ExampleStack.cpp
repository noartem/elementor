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

std::shared_ptr<Element> stackBasicExample() {
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

std::shared_ptr<Element> tooltipPlacementExample(TooltipPlacement placement) {
    auto tooltipElement = tooltip();
    std::shared_ptr<Background> backgroundElement = background();
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

std::shared_ptr<Element> tooltipExample() {
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

std::shared_ptr<Element> comboxExample() {
    return combox()
        ->setPlaceholder("Выберите породу собак")
        ->addOption("лабрадор ретривер", "Лабрадор ретривер - дружелюбный и энергичный")
        ->addOption("немецкая овчарка", "Немецкая овчарка - умная и преданная")
        ->addOption("бульдог", "Бульдог - спокойный и ласковый")
        ->addOption("боксер", "Боксер - смелый и игривый")
        ->addOption("пудель", "Пудель - интеллектуальный и элегантный")
        ->addOption("бигль", "Бигль - жизнерадостный и пылкий")
        ->addOption("хаски", "Хаски - энергичный и независимый")
        ->addOption("далматин", "Далматин - элегантный и энергичный")
        ->addOption("чихуахуа", "Чихуахуа - маленький и оживленный")
        ->addOption("ротвейлер", "Ротвейлер - защитник и преданный")
        ->addOption("французский бульдог", "Французский бульдог - игривый и общительный")
        ->addOption("джек рассел терьер", "Джек рассел терьер - энергичный и умный")
        ->addOption("шотландская овчарка", "Шотландская овчарка - преданный и выносливый")
        ->addOption("бернский зенненхунд", "Бернский зенненхунд - дружелюбный и семейный")
        ->addOption("боксерский бульдог", "Боксерский бульдог - дружелюбный и защитник")
        ->addOption("пекинес", "Пекинес - самоуверенный и независимый")
        ->addOption("австралийская овчарка", "Австралийская овчарка - энергичная и работоспособная")
        ->addOption("мопс", "Мопс - веселый и любопытный")
        ->addOption("ретривер", "Ретривер - дружелюбный и покладистый")
        ->addOption("шпиц", "Шпиц - умный и преданный");
}

std::shared_ptr<Element> ExampleStack::getScene(std::shared_ptr<ApplicationContext> ctx) {
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

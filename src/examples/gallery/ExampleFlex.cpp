//
// Created by noartem on 30.05.2022.
//

#include "ExampleFlex.h"

std::string ExampleFlex::getName() {
    return "Flex";
}

std::string ExampleFlex::getDescription() {
    return "Flex allows you to easily build complex and yet flexible layout";
}

std::shared_ptr<Element> exampleChildren() {
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

std::shared_ptr<Element> exampleAlignmentItem(FlexAlignment alignment) {
    return flex()
        ->setSpacing(8)
        ->setAlignment(alignment)
        ->appendChild(width()
            ->setWidth(128)
            ->setChild(height()
                ->setHeight(96)
                ->setChild(box("#CDE8D9"))))
        ->appendChild(width()
            ->setWidth(128)
            ->setChild(height()
                ->setHeight(192)
                ->setChild(box("#BEE8FA"))))
        ->appendChild(width()
            ->setWidth(96)
            ->setChild(height()
                ->setHeight(128)
                ->setChild(box("#CDE8D9"))));
}

std::shared_ptr<Element> exampleAlignment() {
    return padding()
        ->setPaddings(12, 18)
        ->setChild(flex()
            ->setSpacing(12)
            ->setDirection(FlexDirection::Column)
            ->appendChild(flexible()
                ->setChild(exampleAlignmentItem(FlexAlignment::Start)))
            ->appendChild(flexible()
                ->setChild(exampleAlignmentItem(FlexAlignment::Center)))
            ->appendChild(flexible()
                ->setChild(exampleAlignmentItem(FlexAlignment::End))));
}

std::shared_ptr<Element> exampleCrossAlignmentItem(FlexCrossAlignment crossAlignment) {
    return flex()
        ->setSpacing(8)
        ->setCrossAlignment(crossAlignment)
        ->appendChild(width()
            ->setWidth(128)
            ->setChild(height()
                ->setHeight(96)
                ->setChild(box("#CDE8D9"))))
        ->appendChild(width()
            ->setWidth(128)
            ->setChild(height()
                ->setHeight(192)
                ->setChild(box("#BEE8FA"))))
        ->appendChild(width()
            ->setWidth(96)
            ->setChild(height()
                ->setHeight(128)
                ->setChild(box("#CDE8D9"))));
}

std::shared_ptr<Element> exampleCrossAlignment() {
    return padding()
        ->setPaddings(12, 18)
        ->setChild(flex()
            ->setSpacing(12)
            ->setDirection(FlexDirection::Column)
            ->appendChild(flexible()
                ->setChild(exampleCrossAlignmentItem(FlexCrossAlignment::Start)))
            ->appendChild(flexible()
                ->setChild(exampleCrossAlignmentItem(FlexCrossAlignment::Center)))
            ->appendChild(flexible()
                ->setChild(exampleCrossAlignmentItem(FlexCrossAlignment::End)))
            ->appendChild(flexible()
                ->setChild(exampleCrossAlignmentItem(FlexCrossAlignment::SpaceBetween)))
            ->appendChild(flexible()
                ->setChild(exampleCrossAlignmentItem(FlexCrossAlignment::SpaceEvenly))));
}

std::shared_ptr<Element> ExampleFlex::getScene(std::shared_ptr<ApplicationContext> ctx) {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(48)
                ->appendChild(height()
                    ->setHeight(512)
                    ->setChild(column()
                        ->setSpacing(6)
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(16)
                            ->setText("Flex children can be flexible or sized"))
                        ->appendChild(exampleChildren())))
                ->appendChild(height()
                    ->setHeight(512)
                    ->setChild(column()
                        ->setSpacing(6)
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(16)
                        ->setText("Flex children can be aligned by main axis"))
                        ->appendChild(exampleAlignment())))
                ->appendChild(height()
                    ->setHeight(512)
                    ->setChild(column()
                        ->setSpacing(6)
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(16)
                        ->setText("Flex children can be aligned by cross axis"))
                        ->appendChild(exampleCrossAlignment())))));
}
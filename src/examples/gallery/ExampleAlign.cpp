//
// Created by noartem on 29.05.2022.
//

#include "ExampleAlign.h"
#include "components/Scroll.h"

std::string ExampleAlign::getName() {
    return "Align";
}

std::string ExampleAlign::getDescription() {
    return "Align child in bigger element";
}

Element *exampleAlignWidthItem(float coef, float childCoef) {
    return height()
        ->setHeight(36)
        ->setChild(background()
            ->setColor("#BEE8FA")
            ->setChild(alignWidth()
                ->setCoef(coef, childCoef)
                ->setChild(width()
                    ->setWidth(128)
                    ->setChild(rounded()
                        ->setRadius(8)
                        ->setChild(background()
                            ->setColor("#006C4C")
                            ->setChild(flex()
                                ->setSpacing(8)
                                ->setAlignment(FlexAlignment::Center)
                                ->setCrossAlignment(FlexCrossAlignment::SpaceEvenly)
                                ->appendChild(text()
                                    ->setFontSize(16)
                                    ->setFontColor("#FFFFFF")
                                    ->setText(floatToString(coef)))
                                ->appendChild(text()
                                    ->setFontSize(16)
                                    ->setFontColor("#FFFFFF")
                                    ->setText(floatToString(childCoef)))))))));
}

Element *exampleAlignWidth() {
    return column()
        ->setSpacing(8)
        ->appendChild(exampleAlignWidthItem(0, 1))
        ->appendChild(exampleAlignWidthItem(0, 0.5))
        ->appendChild(exampleAlignWidthItem(0, 0))
        ->appendChild(exampleAlignWidthItem(0.5, 0.5))
        ->appendChild(exampleAlignWidthItem(1, 1))
        ->appendChild(exampleAlignWidthItem(1, 0.5))
        ->appendChild(exampleAlignWidthItem(1, 0));
}

Element *exampleAlignHeightItem(float coef, float childCoef) {
    return flexible()
        ->setChild(background()
            ->setColor("#BEE8FA")
            ->setChild(alignHeight()
                ->setCoef(coef, childCoef)
                ->setChild(height()
                    ->setHeight(128)
                    ->setChild(rounded()
                        ->setRadius(8)
                        ->setChild(background()
                            ->setColor("#006C4C")
                            ->setChild(flex()
                                ->setSpacing(8)
                                ->setDirection(FlexDirection::Column)
                                ->setAlignment(FlexAlignment::Center)
                                ->setCrossAlignment(FlexCrossAlignment::SpaceEvenly)
                                ->appendChild(text()
                                    ->setFontSize(16)
                                    ->setFontColor("#FFFFFF")
                                    ->setText(floatToString(coef)))
                                ->appendChild(text()
                                    ->setFontSize(16)
                                    ->setFontColor("#FFFFFF")
                                    ->setText(floatToString(childCoef)))))))));
}

Element *exampleAlignHeight() {
    return height()
        ->setHeight(512)
        ->setChild(flex()
            ->setSpacing(8)
            ->appendChild(exampleAlignHeightItem(0, 1))
            ->appendChild(exampleAlignHeightItem(0, 0.5))
            ->appendChild(exampleAlignHeightItem(0, 0))
            ->appendChild(exampleAlignHeightItem(0.5, 0.5))
            ->appendChild(exampleAlignHeightItem(1, 1))
            ->appendChild(exampleAlignHeightItem(1, 0.5))
            ->appendChild(exampleAlignHeightItem(1, 0)));
}

Element *exampleCenter() {
    return height()
        ->setHeight(256)
        ->setChild(background()
            ->setColor("#BEE8FA")
            ->setChild(center()
                ->setChild(rounded()
                    ->setRadius(8)
                    ->setChild(width()
                        ->setWidth(64)
                        ->setChild(height()
                            ->setHeight(64)
                            ->setChild(background()
                                ->setColor("#006C4C")))))));
}

Element *ExampleAlign::getScene(ApplicationContext *ctx) {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(12)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Align width"))
                ->appendChild(padding()
                    ->setPaddings(0, 128)
                    ->setChild(exampleAlignWidth()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Align height"))
                ->appendChild(padding()
                    ->setPaddings(128)
                    ->setChild(exampleAlignHeight()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Center"))
                ->appendChild(padding()
                    ->setPaddings(0, 128)
                    ->setChild(exampleCenter()))));
}

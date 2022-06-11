//
// Created by noartem on 29.05.2022.
//

#include "ExampleBackground.h"
#include "Scroll.h"

std::string ExampleBackground::getName() {
    return "Background";
}

std::string ExampleBackground::getDescription() {
    return "Background fills element with color";
}

Element *ExampleBackground::getScene() {
    return scroll()
        ->setChild(padding()
            ->setPaddings(12, 18)
            ->setChild(column()
                ->setSpacing(12)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("RGB color"))
                ->appendChild(height()
                    ->setHeight(40)
                    ->setChild(background()
                        ->setColor(0, 108, 76)))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("RGBA color"))
                ->appendChild(height()
                    ->setHeight(40)
                    ->setChild(background()
                        ->setColor(0, 108, 76, 128)))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Hex color"))
                ->appendChild(height()
                    ->setHeight(40)
                    ->setChild(background()
                        ->setColor("#006C4C")))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Skia color"))
                ->appendChild(height()
                    ->setHeight(40)
                    ->setChild(background()
                        ->setColor(SK_ColorBLUE)))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Background with child"))
                ->appendChild(height()
                    ->setHeight(40)
                    ->setChild(background()
                        ->setColor("#BEE8FA")
                        ->setChild(padding()
                            ->setPaddings(12)
                            ->setChild(background()
                                ->setColor("006C4C")))))));
}

//
// Created by noartem on 11.06.2022.
//

#include "ExampleText.h"
#include "Scroll.h"

std::string ExampleText::getName() {
    return "Text";
}

std::string ExampleText::getDescription() {
    return "Display text with various styles";
}

Element *exampleColor() {
    Column *examples = column()
        ->setSpacing(12);

    for (std::string color : {"#006C4C", "#4B6358", "#3A6373", "#C01D24"}) {
        examples
            ->appendChild(text()
                ->setFontColor(color)
                ->setFontWeight(600)
                ->setText("Font color #" + color));
    }

    return examples;
}

Element *exampleSize() {
    Column *examples = column()
        ->setSpacing(12);

    for (int size : {12, 14, 16, 18, 24}) {
        examples
            ->appendChild(text()
                ->setFontSize(size)
                ->setFontColor("#062016")
                ->setText("Font size " + std::to_string(size) + "px"));
    }

    return examples;
}

Element *exampleSlant() {
    return column()
        ->setSpacing(12)
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSlant(FontSlant::Upright)
            ->setText("Font slant Upright"))
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSlant(FontSlant::Italic)
            ->setText("Font slant Italic"))
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSlant(FontSlant::Oblique)
            ->setText("Font slant Oblique"));
}

Element *exampleWeight() {
    Column *examples = column()
        ->setSpacing(12);

    for (int weight : {300, 400, 500, 550, 600, 700, 900}) {
        examples
            ->appendChild(text()
                ->setFontColor("#062016")
                ->setFontWeight(weight)
                ->setText("Font weight " + std::to_string(weight)));
    }

    return examples;
}

Element *exampleEdging() {
    return column()
        ->setSpacing(12)
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSize(48)
            ->setFontEdging(FontEdging::Alias)
            ->setText("Font edging Alias"))
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSize(48)
            ->setFontEdging(FontEdging::AntiAlias)
            ->setText("Font edging AntiAlias"))
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSize(48)
            ->setFontEdging(FontEdging::SubpixelAntiAlias)
            ->setText("Font edging SubpixelAntiAlias"));
}

Element *exampleFontFamily() {
    Column *examples = column()
        ->setSpacing(12);

    for (std::string fontFamily : {"Times New Roman", "Fira Code", "Roboto", "DejaVu Sans", "Comic Sans MS"}) {
        examples
            ->appendChild(text()
                ->setFontColor("#062016")
                ->setFontFamily(fontFamily)
                ->setFontSize(24)
                ->setText("Font family \"" + fontFamily + "\""));
    }

    return examples;
}

Element *ExampleText::getScene() {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(24)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Font color"))
                ->appendChild(padding()
                    ->setPaddings(0, 16)
                    ->setChild(exampleColor()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Font size"))
                ->appendChild(padding()
                    ->setPaddings(0, 16)
                    ->setChild(exampleSize()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Font slant"))
                ->appendChild(padding()
                    ->setPaddings(0, 16)
                    ->setChild(exampleSlant()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Font weight"))
                ->appendChild(padding()
                    ->setPaddings(0, 16)
                    ->setChild(exampleWeight()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Font edging"))
                ->appendChild(padding()
                    ->setPaddings(0, 16)
                    ->setChild(exampleEdging()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Font family"))
                ->appendChild(padding()
                    ->setPaddings(0, 16)
                    ->setChild(exampleFontFamily()))));
}

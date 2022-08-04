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
                ->setText("Font color " + color));
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

Element *exampleParagraph() {
    return column()
        ->setSpacing(12)
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSize(16)
            ->setText("General paragraph"))
        ->appendChild(rounded()
            ->setRadius(8)
            ->setChild(background()
                ->setColor("#EDF5F0")
                ->setChild(padding()
                    ->setPaddings(24)
                    ->setChild(paragraph()
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(16)
                            ->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque pharetra enim ut enim laoreet hendrerit. In magna diam, suscipit vitae aliquet sed, laoreet non nulla. Duis vitae mauris a nibh eleifend pretium. Nunc tincidunt gravida ex sed rutrum. In erat lectus, scelerisque vitae dolor dignissim, egestas lobortis risus. Morbi tincidunt ante ac quam fringilla consequat. Curabitur ullamcorper arcu luctus lorem feugiat, at suscipit augue consectetur. Etiam sit amet augue facilisis, porta turpis nec, feugiat lorem. Sed mattis, leo nec semper interdum, elit libero sollicitudin est, ac tincidunt diam urna sit amet nibh. Aliquam erat volutpat. Quisque euismod ipsum id lorem vulputate dictum. Curabitur leo quam, blandit non malesuada ut, vehicula id eros. Maecenas fringilla faucibus sem. Morbi quis odio tempus enim vestibulum auctor nec at nibh. Vestibulum lacinia nulla ut eros iaculis rutrum. Morbi fringilla cursus metus, sed finibus arcu pretium ut."))))))
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSize(16)
            ->setText("Paragraph with text align right"))
        ->appendChild(rounded()
            ->setRadius(8)
            ->setChild(background()
                ->setColor("#EDF5F0")
                ->setChild(padding()
                    ->setPaddings(24)
                    ->setChild(paragraph()
                        ->setTextAlign(TextAlign::Right)
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(16)
                            ->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque pharetra enim ut enim laoreet hendrerit. In magna diam, suscipit vitae aliquet sed, laoreet non nulla. Duis vitae mauris a nibh eleifend pretium. Nunc tincidunt gravida ex sed rutrum. In erat lectus, scelerisque vitae dolor dignissim, egestas lobortis risus. Morbi tincidunt ante ac quam fringilla consequat. Curabitur ullamcorper arcu luctus lorem feugiat, at suscipit augue consectetur. Etiam sit amet augue facilisis, porta turpis nec, feugiat lorem. Sed mattis, leo nec semper interdum, elit libero sollicitudin est, ac tincidunt diam urna sit amet nibh. Aliquam erat volutpat. Quisque euismod ipsum id lorem vulputate dictum. Curabitur leo quam, blandit non malesuada ut, vehicula id eros. Maecenas fringilla faucibus sem. Morbi quis odio tempus enim vestibulum auctor nec at nibh. Vestibulum lacinia nulla ut eros iaculis rutrum. Morbi fringilla cursus metus, sed finibus arcu pretium ut."))))))
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSize(16)
            ->setText("Paragraph with text align justify"))
        ->appendChild(rounded()
            ->setRadius(8)
            ->setChild(background()
                ->setColor("#EDF5F0")
                ->setChild(padding()
                    ->setPaddings(24)
                    ->setChild(paragraph()
                        ->setTextAlign(TextAlign::Justify)
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(16)
                            ->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque pharetra enim ut enim laoreet hendrerit. In magna diam, suscipit vitae aliquet sed, laoreet non nulla. Duis vitae mauris a nibh eleifend pretium. Nunc tincidunt gravida ex sed rutrum. In erat lectus, scelerisque vitae dolor dignissim, egestas lobortis risus. Morbi tincidunt ante ac quam fringilla consequat. Curabitur ullamcorper arcu luctus lorem feugiat, at suscipit augue consectetur. Etiam sit amet augue facilisis, porta turpis nec, feugiat lorem. Sed mattis, leo nec semper interdum, elit libero sollicitudin est, ac tincidunt diam urna sit amet nibh. Aliquam erat volutpat. Quisque euismod ipsum id lorem vulputate dictum. Curabitur leo quam, blandit non malesuada ut, vehicula id eros. Maecenas fringilla faucibus sem. Morbi quis odio tempus enim vestibulum auctor nec at nibh. Vestibulum lacinia nulla ut eros iaculis rutrum. Morbi fringilla cursus metus, sed finibus arcu pretium ut."))))))
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSize(16)
            ->setText("Multiple pargraphs"))
        ->appendChild(rounded()
            ->setRadius(8)
            ->setChild(background()
                ->setColor("#EDF5F0")
                ->setChild(padding()
                    ->setPaddings(24)
                    ->setChild(paragraph()
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(16)
                            ->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque pharetra enim ut enim laoreet hendrerit. In magna diam, suscipit vitae aliquet sed, laoreet non nulla. Duis vitae mauris a nibh eleifend pretium. Nunc tincidunt gravida ex sed rutrum. In erat lectus, scelerisque vitae dolor dignissim, egestas lobortis risus. Morbi tincidunt ante ac quam fringilla consequat. Curabitur ullamcorper arcu luctus lorem feugiat, at suscipit augue consectetur. Etiam sit amet augue facilisis, porta turpis nec, feugiat lorem. Sed mattis, leo nec semper interdum, elit libero sollicitudin est, ac tincidunt diam urna sit amet nibh. Aliquam erat volutpat. Quisque euismod ipsum id lorem vulputate dictum. Curabitur leo quam, blandit non malesuada ut, vehicula id eros. Maecenas fringilla faucibus sem. Morbi quis odio tempus enim vestibulum auctor nec at nibh. Vestibulum lacinia nulla ut eros iaculis rutrum. Morbi fringilla cursus metus, sed finibus arcu pretium ut.\n\nSed fermentum tellus non magna sagittis scelerisque. Aenean non nulla tincidunt nunc scelerisque faucibus. Phasellus elementum pellentesque risus, at pretium sapien suscipit ac. Etiam at tincidunt purus. Nulla euismod dolor in lacus eleifend, blandit semper diam volutpat. Vivamus accumsan orci id magna placerat efficitur vel sagittis elit. Aenean est nibh, porta non quam ac, suscipit molestie odio. Proin sit amet tincidunt arcu. Nulla maximus id neque sed ullamcorper. Duis consequat est ut orci condimentum malesuada. Integer aliquam pulvinar ex eget maximus. Nam ultricies, elit ac posuere condimentum, ante nisi posuere arcu, vitae venenatis ex nulla in tellus.\n\nEtiam sagittis urna at lacus pulvinar eleifend et quis mauris. Donec pellentesque hendrerit tempor. Vestibulum elit metus, ornare sed nunc id, venenatis molestie magna. Vivamus eget tincidunt dolor, et dignissim turpis. Suspendisse varius feugiat sem, id condimentum dolor commodo faucibus. Nullam a turpis egestas, pharetra nunc vel, dapibus ligula. Curabitur viverra consequat ligula a molestie. Vestibulum a elit mattis, maximus dolor eu, imperdiet eros. Donec eu tempor enim. Pellentesque sit amet ultrices nisi. Mauris accumsan lacus vel mollis pretium."))))))
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSize(16)
            ->setText("Multi elements paragraph"))
        ->appendChild(rounded()
            ->setRadius(8)
            ->setChild(background()
                ->setColor("#EDF5F0")
                ->setChild(padding()
                    ->setPaddings(24)
                    ->setChild(paragraph()
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(20)
                            ->setText("Lorem ipsum dolor sit amet"))
                        ->appendChild(text()
                            ->setFontColor("#006C4C")
                            ->setFontSize(16)
                            ->setText(", consectetur adipiscing elit"))
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSlant(FontSlant::Italic)
                            ->setFontSize(16)
                            ->setText(". Pellentesque pharetra enim ut enim laoreet hendrerit. In magna diam, suscipit vitae aliquet sed, laoreet non nulla. "))
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(16)
                            ->setFontWeight(550)
                            ->setText("Duis vitae mauris a nibh eleifend pretium. "))
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(16)
                            ->setText("Nunc tincidunt gravida ex sed rutrum. In erat lectus, scelerisque vitae dolor dignissim, egestas lobortis risus. Morbi tincidunt ante ac quam fringilla consequat. Curabitur ullamcorper arcu luctus lorem feugiat, at suscipit augue consectetur. Etiam sit amet augue facilisis, porta turpis nec, feugiat lorem. Sed mattis, leo nec semper interdum, elit libero sollicitudin est, ac tincidunt diam urna sit amet nibh. "))
                        ->appendChild(text()
                            ->setFontColor("#C01D24")
                            ->setFontSize(16)
                            ->setText("Morbi fringilla cursus metus, sed finibus arcu pretium ut."))))))
        ->appendChild(text()
            ->setFontColor("#062016")
            ->setFontSize(16)
            ->setText("Paragraph RTL"))
        ->appendChild(rounded()
            ->setRadius(8)
            ->setChild(background()
                ->setColor("#EDF5F0")
                ->setChild(padding()
                    ->setPaddings(16)
                    ->setChild(paragraph()
                        ->setTextDirection(TextDirection::RTL)
                        ->setTextAlign(TextAlign::Right)
                        ->appendChild(text()
                            ->setFontColor("#062016")
                            ->setFontSize(16)
                            ->setText("كيفية عمل Cheesecake بالتوت البري\nأهلا وسهلا بك في المقال!\nسوف تتعلم كيفية تحضير موقعك ليعمل باللغات من اليمين إلى اليسار."))))));
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
                    ->setChild(exampleFontFamily()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Paragraph"))
                ->appendChild(padding()
                    ->setPaddings(0, 16)
                    ->setChild(exampleParagraph()))));
}

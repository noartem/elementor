//
// Created by noartem on 26.07.2022.
//

#include "ExampleImage.h"

#include <filesystem>

std::string ExampleImage::getName() {
    return "Image";
}

std::string ExampleImage::getDescription() {
    return "Image in one of these formats: BMP, GIF, HEIF, ICO, JPEG, PNG, WBMP, WebP";
}

std::shared_ptr<Element> ExampleImage::getScene(std::shared_ptr<ApplicationContext> ctx) {
    std::string currentPath = std::filesystem::current_path().string() + "/../../../../";

    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(12)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Image"))
                ->appendChild(alignWidth()
                    ->setChild(image()
                        ->fromPath(currentPath + "src/examples/gallery/test.png")))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Sized image"))
                ->appendChild(width()
                    ->setWidth(512)
                    ->setChild(height()
                        ->setHeight(512)
                        ->setChild(image()
                            ->fromPath(currentPath + "src/examples/gallery/test.png"))))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Wrong sized image"))
                ->appendChild(width()
                    ->setWidth(512)
                    ->setChild(height()
                        ->setHeight(256)
                        ->setChild(image()
                            ->fromPath(currentPath + "src/examples/gallery/test.png"))))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Transparent image"))
                ->appendChild(row()
                    ->setSpacing(12)
                    ->appendChild(background()
                        ->setColor("#FFAAAA")
                        ->setChild(padding()
                            ->setPaddings(12)
                            ->setChild(width()
                                ->setWidth(128)
                                ->setChild(height()
                                    ->setHeight(128)
                                    ->setChild(image()
                                        ->fromPath(currentPath + "src/examples/gallery/test-transparent.png"))))))
                    ->appendChild(background()
                        ->setColor("#AAFFAA")
                        ->setChild(padding()
                            ->setPaddings(12)
                            ->setChild(width()
                                ->setWidth(128)
                                ->setChild(height()
                                    ->setHeight(128)
                                    ->setChild(image()
                                        ->fromPath(currentPath + "src/examples/gallery/test-transparent.png"))))))
                    ->appendChild(background()
                        ->setColor("#AAAAFF")
                        ->setChild(padding()
                            ->setPaddings(12)
                            ->setChild(width()
                                ->setWidth(128)
                                ->setChild(height()
                                    ->setHeight(128)
                                    ->setChild(image()
                                        ->fromPath(currentPath + "src/examples/gallery/test-transparent.png")))))))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Fit size contain"))
                ->appendChild(background()
                    ->setColor("#EDF5F0")
                    ->setChild(height()
                        ->setHeight(512)
                        ->setChild(fitContain()
                            ->setChild(width()
                                ->setWidth(2048)
                                ->setChild(height()
                                    ->setHeight(2048)
                                    ->setChild(image()
                                        ->fromPath(currentPath + "src/examples/gallery/test.png")))))))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Fit size cover"))
                ->appendChild(background()
                    ->setColor("#EDF5F0")
                    ->setChild(height()
                        ->setHeight(512)
                        ->setChild(fitCover()
                            ->setChild(image()
                                ->fromPath(currentPath + "src/examples/gallery/test.png")))))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("SVG"))
                ->appendChild(height()
                    ->setHeight(256)
                    ->setChild(svg()
                        ->fromPath(currentPath + "src/examples/gallery/test.svg")))
                ->appendChild(height()
                    ->setHeight(512)
                    ->setChild(svg()
                        ->fromPath(currentPath + "src/examples/gallery/test.svg")))
                ->appendChild(height()
                    ->setHeight(1024)
                    ->setChild(svg()
                        ->fromPath(currentPath + "src/examples/gallery/test.svg")))));
}

//
// Created by noartem on 20.08.2022.
//

#include "ScaleControl.h"

#include <filesystem>

ScaleControl *scaleControl() {
    return new ScaleControl();
}

ScaleControl::ScaleControl() {
    std::string currentPath = std::filesystem::current_path().string() + "/../../../../";

    this->scalePercentageText = text();

    this->child = height()
        ->setHeight(36)
        ->setChild(flex()
            ->appendChild(width()
                ->setWidth(36)
                ->setChild(clickable()
                    ->onClick([this] () { this->decrementScale(); })
                    ->setChild(rounded()
                        ->setRadius(8, 0, 0, 8)
                        ->setChild(background()
                            ->setColor("#006C4C")
                            ->setChild(padding()
                                ->setPaddings(8)
                                ->setChild(svg()
                                    ->fromPath(currentPath + "src/examples/gallery/remove.svg")))))))
            ->appendChild(flexible()
                ->setChild(background()
                    ->setColor("#CDE8D9")
                    ->setChild(padding()
                        ->setPaddings(8)
                        ->setChild(center()
                            ->setChild(this->scalePercentageText
                                ->setFontColor("#062016")
                                ->setFontSize(16)
                                ->setText(std::to_string(this->scalePercentage) + "%"))))))
            ->appendChild(width()
                ->setWidth(36)
                ->setChild(clickable()
                    ->onClick([this] () { this->incrementScale(); })
                    ->setChild(rounded()
                        ->setRadius(0, 8, 8, 0)
                        ->setChild(background()
                            ->setColor("#006C4C")
                            ->setChild(padding()
                                ->setPaddings(8)
                                ->setChild(svg()
                                    ->fromPath(currentPath + "src/examples/gallery/add.svg"))))))));
}

void ScaleControl::applyScale() {
    this->scalePercentageText->setText(std::to_string(this->scalePercentage) + "%");
    this->ctx->setPixelScale((((float) this->scalePercentage) / 100) * this->initialPixelScale);
}

void ScaleControl::incrementScale() {
    this->scalePercentage += 10;
    this->applyScale();
}

void ScaleControl::decrementScale() {
    this->scalePercentage -= 10;
    this->applyScale();
}

Size ScaleControl::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
    return this->child->getSize(ctx, window, boundaries);
}

std::vector <RenderElement> ScaleControl::getChildren(ApplicationContext *ctx, Window *window, Size size) {
    this->ctx = ctx;
    if (this->initialPixelScale == 0) {
        this->initialPixelScale = ctx->getPixelScale();
    }

    RenderElement child;
    child.element = this->child;
    child.size = size;
    child.position = {0, 0};
    return {child};
}
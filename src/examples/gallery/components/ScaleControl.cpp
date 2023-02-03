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

    Background *decrementBackground = background();
    Background *incrementBackground = background();

    this->child = height()
        ->setHeight(36)
        ->setChild(rounded()
            ->setRadius(8)
            ->setChild(background()
                ->setColor("#DEEDE6")
                ->setChild(flex()
                    ->appendChild(width()
                        ->setWidth(36)
                        ->setChild(clickable()
                            ->onClick([this] () { this->decrementScale(); })
                            ->setChild(hoverable()
                                ->onEnter([decrementBackground] () { decrementBackground->setColor("#C2DDD3"); })
                                ->onLeave([decrementBackground] () { decrementBackground->setColor("#DEEDE6"); })
                                ->setChild(decrementBackground
                                    ->setColor("#DEEDE6")
                                    ->setChild(padding()
                                        ->setPaddings(8)
                                        ->setChild(svg()
                                            ->fromPath(currentPath + "src/examples/gallery/remove.svg")))))))
                    ->appendChild(flexible()
                        ->setChild(padding()
                            ->setPaddings(8)
                            ->setChild(center()
                                ->setChild(this->scalePercentageText
                                    ->setFontColor("#3F4944")
                                    ->setFontSize(16)
                                    ->setFontWeight(500)
                                    ->setFontFamily("Fira Code")
                                    ->setText(std::to_string(this->scalePercentage) + "%")))))
                    ->appendChild(width()
                        ->setWidth(36)
                        ->setChild(clickable()
                            ->onClick([this] () { this->incrementScale(); })
                            ->setChild(hoverable()
                                ->onEnter([incrementBackground] () { incrementBackground->setColor("#C2DDD3"); })
                                ->onLeave([incrementBackground] () { incrementBackground->setColor("#DEEDE6"); })
                                ->setChild(incrementBackground
                                    ->setColor("#DEEDE6")
                                    ->setChild(padding()
                                        ->setPaddings(8)
                                        ->setChild(svg()
                                            ->fromPath(currentPath + "src/examples/gallery/add.svg"))))))))));
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
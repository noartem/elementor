//
// Created by noartem on 20.08.2022.
//

#include "ScaleControl.h"
#include "icons.h"

#include <filesystem>

namespace elementor::components {
    ScaleControl *scaleControl() {
        return new ScaleControl();
    }

    ScaleControl::ScaleControl() {
        std::string currentPath = std::filesystem::current_path().string() + "/../../../../";

        this->scalePercentageText = text();

        std::shared_ptr<Background> decrementBackground = background();
        std::shared_ptr<Background> incrementBackground = background();

        this->element = height()
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
                                                ->fromPath(currentPath + "src/components/remove.svg")))))))
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
                                                ->fromPath(currentPath + "src/components/add.svg"))))))))));
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

    std::vector<RenderElement> ScaleControl::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        if (this->initialPixelScale == 0) {
            this->initialPixelScale = ctx->getPixelScale();
        }

        return Component::getChildren(ctx, window, rect);
    }
}
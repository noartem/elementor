//
// Created by noartem on 03.08.2022.
//

#include "FPSLabel.h"

namespace elementor::components {
    FPSLabel *fpsLabel() {
        return new FPSLabel();
    }

    FPSLabel::FPSLabel() {
        this->textElement = text();
        this->element = height()
            ->setHeight(36)
            ->setChild(rounded()
                ->setRadius(8)
                ->setChild(background()
                    ->setColor("#DEEDE6")
                    ->setChild(center()
                        ->setChild(this->textElement
                            ->setFontColor("#3F4944")
                            ->setFontSize(16)
                            ->setFontWeight(500)
                            ->setFontFamily("Fira Code")
                            ->setText("FPS: 000")))));
    }

    std::vector<RenderElement> FPSLabel::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        ctx->requestNextFrame([] {});
        this->textElement->setText("FPS: " + std::to_string((int) ctx->getPerfomance()->getFPS()));

        return Component::getChildren(ctx, window, rect);
    }
}
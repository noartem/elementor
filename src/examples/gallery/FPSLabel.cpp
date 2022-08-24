//
// Created by noartem on 03.08.2022.
//

#include "FPSLabel.h"

FPSLabel *fpsLabel() {
    return new FPSLabel();
}

FPSLabel::FPSLabel() {
    this->childText = text();
    this->child = height()
        ->setHeight(36)
        ->setChild(rounded()
            ->setRadius(8)
            ->setChild(background()
                ->setColor("#DEEDE6")
                ->setChild(center()
                    ->setChild(this->childText
                        ->setFontColor("#3F4944")
                        ->setFontSize(16)
                        ->setFontWeight(500)
                        ->setFontFamily("Fira Code")
                        ->setText("FPS: 000")))));
}

Size FPSLabel::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
    return this->child->getSize(ctx, window, boundaries);
}

std::vector <RenderElement> FPSLabel::getChildren(ApplicationContext *ctx, Window *window, Size size) {
    ctx->requestNextFrame([] {});
    this->childText->setText("FPS: " + std::to_string((int) ctx->getPerfomance()->getFPS()));

    RenderElement child;
    child.element = this->child;
    child.size = size;
    child.position = {0, 0};
    return {child};
}
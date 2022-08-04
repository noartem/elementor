//
// Created by noartem on 03.08.2022.
//

#include "FPSLabel.h"

FPSLabel *fpsLabel() {
    return new FPSLabel();
}

FPSLabel::FPSLabel() {
    this->child = text()
        ->setFontColor("#062016")
        ->setFontSize(16)
        ->setText("FPS: 00");
}

Size FPSLabel::getSize(ApplicationContext *ctx, Boundaries boundaries) {
    return this->child->getSize(ctx, boundaries);
}

std::vector <RenderElement> FPSLabel::getChildren(ApplicationContext *ctx, Size size) {
    this->child->setText("FPS: " + std::to_string((int) ctx->perfomance->getFPS()));

    RenderElement child;
    child.element = this->child;
    child.size = size;
    child.position = {0, 0};
    return {child};
}
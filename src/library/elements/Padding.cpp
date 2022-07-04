//
// Created by noartem on 13.04.2022.
//

#include "Padding.h"

namespace elementor::elements {
    Padding *padding() {
        return new Padding();
    }

    Padding *Padding::setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft) {
        this->paddings = {paddingTop, paddingRight, paddingBottom, paddingLeft};
        return this;
    }

    Padding *Padding::setPaddings(float paddingTop, float paddingX, float paddingBottom) {
        this->setPaddings(paddingTop, paddingX, paddingBottom, paddingX);
        return this;
    }

    Padding *Padding::setPaddings(float paddingY, float paddingX) {
        this->setPaddings(paddingY, paddingX, paddingY, paddingX);
        return this;
    }

    Padding *Padding::setPaddings(float paddingYX) {
        this->setPaddings(paddingYX, paddingYX, paddingYX, paddingYX);
        return this;
    }

    PaddingsValue Padding::getPaddings() {
        return this->paddings;
    }

    Padding *Padding::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Padding::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->hasChild()) {
            float paddingTop = this->getPaddings().top * ctx->monitorPixelScale;
            float paddingBottom = this->getPaddings().bottom * ctx->monitorPixelScale;
            float paddingY = paddingTop + paddingBottom;

            float paddingRight = this->getPaddings().right * ctx->monitorPixelScale;
            float paddingLeft = this->getPaddings().left * ctx->monitorPixelScale;
            float paddingX = paddingLeft + paddingRight;

            Boundaries childBoundaries = {{boundaries.min.width - paddingX, boundaries.min.height - paddingY}, {boundaries.max.width - paddingX, boundaries.max.height - paddingY}};
            Size childSize = this->getChild()->getSize(ctx, childBoundaries);
            return {childSize.width + paddingX, childSize.height + paddingY};
        } else {
            return boundaries.max;
        }
    }

    std::vector <RenderElement> Padding::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();

            float paddingTop = this->getPaddings().top * ctx->monitorPixelScale;
            float paddingRight = this->getPaddings().right * ctx->monitorPixelScale;
            float paddingBottom = this->getPaddings().bottom * ctx->monitorPixelScale;
            float paddingLeft = this->getPaddings().left * ctx->monitorPixelScale;
            child.position = {paddingLeft, paddingTop};

            float childWidth = size.width - paddingLeft - paddingRight;
            float childHeight = size.height - paddingTop - paddingBottom;
            child.size = {childWidth, childHeight};

            children.push_back(child);
        }

        return children;
    }
}

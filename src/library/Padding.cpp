//
// Created by noartem on 13.04.2022.
//

#include "Padding.h"

namespace elementor {
    Padding *padding() {
        return new Padding();
    }

    Padding *Padding::setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft) {
        this->paddings = {paddingTop, paddingLeft, paddingBottom, paddingRight};
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
        child->context = context;
        this->updateChild(child);
        return this;
    }

    int Padding::getPaddingTop() {
        return ceil(this->getPaddings().top * this->context->monitorPixelScale);
    }

    int Padding::getPaddingRight() {
        return ceil(this->getPaddings().right * this->context->monitorPixelScale);
    }

    int Padding::getPaddingBottom() {
        return ceil(this->getPaddings().bottom * this->context->monitorPixelScale);
    }

    int Padding::getPaddingLeft() {
        return ceil(this->getPaddings().left * this->context->monitorPixelScale);
    }

    RenderSize Padding::getSize(RenderBoundaries boundaries) {
        if (this->hasChild()) {
            RenderSize childSize = this->getChild(this->context)->getSize(boundaries);
            int width = childSize.width + this->getPaddingLeft() + this->getPaddingRight();
            int height = childSize.height + this->getPaddingTop() + this->getPaddingBottom();
            RenderSize size = {width, height};
            return fitSizeInBoundaries(size, boundaries);
        } else {
            return boundaries.max;
        }
    }

    std::vector <RenderElement> Padding::getRenderChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild(this->context);

            child.position = {this->getPaddingLeft(), this->getPaddingTop()};

            int childWidth = size.width - (this->getPaddingLeft() + this->getPaddingRight());
            int childHeight = size.height - (this->getPaddingTop() + this->getPaddingBottom());
            child.size = {childWidth, childHeight};

            children.push_back(child);
        }

        return children;
    }
}

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

    Size Padding::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        if (this->hasChild()) {
            float paddingTop = this->getPaddings().top * window->getMonitor()->getPixelScale();
            float paddingBottom = this->getPaddings().bottom * window->getMonitor()->getPixelScale();
            float paddingY = paddingTop + paddingBottom;

            float paddingRight = this->getPaddings().right * window->getMonitor()->getPixelScale();
            float paddingLeft = this->getPaddings().left * window->getMonitor()->getPixelScale();
            float paddingX = paddingLeft + paddingRight;

            Boundaries childBoundaries = {{boundaries.min.width - paddingX, boundaries.min.height - paddingY}, {boundaries.max.width - paddingX, boundaries.max.height - paddingY}};
            Size childSize = this->getChild()->getSize(ctx, window, childBoundaries);
            return {childSize.width + paddingX, childSize.height + paddingY};
        } else {
            return boundaries.max;
        }
    }

    std::vector <RenderElement> Padding::getChildren(ApplicationContext *ctx, Window *window, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();

            float paddingTop = this->getPaddings().top * window->getMonitor()->getPixelScale();
            float paddingRight = this->getPaddings().right * window->getMonitor()->getPixelScale();
            float paddingBottom = this->getPaddings().bottom * window->getMonitor()->getPixelScale();
            float paddingLeft = this->getPaddings().left * window->getMonitor()->getPixelScale();
            child.position = {paddingLeft, paddingTop};

            float childWidth = size.width - paddingLeft - paddingRight;
            float childHeight = size.height - paddingTop - paddingBottom;
            child.size = {childWidth, childHeight};

            children.push_back(child);
        }

        return children;
    }
}

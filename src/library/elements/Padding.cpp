//
// Created by noartem on 13.04.2022.
//

#include "Padding.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<Padding> padding() {
        return std::make_shared<Padding>();
    }

    std::shared_ptr<Padding> Padding::setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft) {
        this->paddings = {paddingTop, paddingRight, paddingBottom, paddingLeft};
        return shared_from_this();
    }

    std::shared_ptr<Padding> Padding::setPaddings(float paddingTop, float paddingX, float paddingBottom) {
        this->setPaddings(paddingTop, paddingX, paddingBottom, paddingX);
        return shared_from_this();
    }

    std::shared_ptr<Padding> Padding::setPaddings(float paddingY, float paddingX) {
        this->setPaddings(paddingY, paddingX, paddingY, paddingX);
        return shared_from_this();
    }

    std::shared_ptr<Padding> Padding::setPaddings(float paddingYX) {
        this->setPaddings(paddingYX, paddingYX, paddingYX, paddingYX);
        return shared_from_this();
    }

    PaddingsValue Padding::getPaddings() {
        return this->paddings;
    }

    std::shared_ptr<Padding> Padding::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size Padding::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        if (this->hasChild()) {
            float paddingTop = this->getPaddings().top * ctx->getPixelScale();
            float paddingBottom = this->getPaddings().bottom * ctx->getPixelScale();
            float paddingY = paddingTop + paddingBottom;

            float paddingRight = this->getPaddings().right * ctx->getPixelScale();
            float paddingLeft = this->getPaddings().left * ctx->getPixelScale();
            float paddingX = paddingLeft + paddingRight;

            Boundaries childBoundaries = {{std::max(boundaries.min.width - paddingX, ZERO), std::max(boundaries.min.height - paddingY, ZERO)}, {std::max(boundaries.max.width - paddingX, ZERO), std::max(boundaries.max.height - paddingY, ZERO)}};
            Size childSize = this->getChild()->getSize(ctx, window, childBoundaries);
            return {childSize.width + paddingX, childSize.height + paddingY};
        } else {
            return boundaries.max;
        }
    }

    std::vector <RenderElement> Padding::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{};
            childElement.element = this->getChild();

            float paddingTop = this->getPaddings().top * ctx->getPixelScale();
            float paddingRight = this->getPaddings().right * ctx->getPixelScale();
            float paddingBottom = this->getPaddings().bottom * ctx->getPixelScale();
            float paddingLeft = this->getPaddings().left * ctx->getPixelScale();
            childElement.position = {paddingLeft, paddingTop};

            float childWidth = rect.size.width - paddingLeft - paddingRight;
            float childHeight = rect.size.height - paddingTop - paddingBottom;
            childElement.size = {childWidth, childHeight};

            children.push_back(childElement);
        }

        return children;
    }
}

//
// Created by noartem on 04.05.2022.
//

#include "Wrap.h"

namespace elementor::elements {
    Wrap *wrap() {
        return new Wrap();
    }

    Wrap *Wrap::setSpacing(float spacing) {
        this->spacing = spacing;
        return this;
    }

    float Wrap::getSpacing() {
        return this->spacing;
    }

    Wrap *Wrap::setCrossSpacing(float spacing) {
        this->crossSpacing = spacing;
        return this;
    }

    float Wrap::getCrossSpacing() {
        return this->crossSpacing;
    }

    Wrap *Wrap::setSpacing(float spacing, float crossSpacing) {
        this->setSpacing(spacing);
        this->setCrossSpacing(crossSpacing);
        return this;
    }

    Wrap *Wrap::setDirection(WrapDirection direction) {
        this->direction = direction;
        return this;
    }

    WrapDirection Wrap::getDirection() {
        return this->direction;
    }

    Wrap *Wrap::appendChild(Element *child) {
        this->addChild(child);
        return this;
    }

    Size Wrap::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        float spacing = this->spacing * ctx->window->monitorPixelScale;
        float crossSpacing = this->crossSpacing * ctx->window->monitorPixelScale;

        bool isRow = this->direction == WrapDirection::Row;
        float maxAxisSize = isRow ? boundaries.max.width : boundaries.max.height;
        float maxCrossAxisSize = isRow ? boundaries.max.height : boundaries.max.width;

        float axisPosition = 0;
        float crossAxisPosition = 0;

        float rowCrossAxisSize = 0;

        for (Element *childElement : this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, {{0, 0}, boundaries.max});

            float axisChildSize = isRow ? childSize.width : childSize.height;
            float crossAxisChildSize = isRow ? childSize.height : childSize.width;
            
            if (axisPosition + axisChildSize > maxAxisSize) {
                axisPosition = 0;
                crossAxisPosition += rowCrossAxisSize + crossSpacing;
            }

            if (crossAxisChildSize > rowCrossAxisSize) {
                rowCrossAxisSize = crossAxisChildSize;
            }

            axisPosition += axisChildSize + spacing;
        }

        float crossAxisSize = crossAxisPosition + rowCrossAxisSize;
        float width = isRow ? boundaries.max.width : crossAxisSize;
        float height = isRow ? crossAxisSize : boundaries.max.height;

        return fitSizeInBoundaries({width, height}, boundaries);
    }

    std::vector <RenderElement> Wrap::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        for (Element *childElement: this->getChildrenList()) {
            RenderElement child;
            child.element = childElement;
            child.size = childElement->getSize(ctx, {{0, 0}, size});
            children.push_back(child);
        }

        float spacing = this->getSpacing() * ctx->window->monitorPixelScale;
        float crossSpacing = this->getCrossSpacing() * ctx->window->monitorPixelScale;

        bool isRow = this->direction == WrapDirection::Row;

        float axisSize = isRow ? size.width : size.height;
        float crossAxisSize = isRow ? size.height : size.width;

        float axisPosition = 0;
        float crossAxisPosition = 0;

        float rowCrossAxisSize = 0;

        for (RenderElement &child : children) {
            float axisChildSize = isRow ? child.size.width : child.size.height;
            float crossAxisChildSize = isRow ? child.size.height : child.size.width;

            if (axisPosition + axisChildSize > axisSize) {
                axisPosition = 0;
                crossAxisPosition += rowCrossAxisSize + crossSpacing;
            }

            if (crossAxisChildSize > rowCrossAxisSize) {
                rowCrossAxisSize = crossAxisChildSize;
            }

            if (isRow) {
                child.position = {axisPosition, crossAxisPosition};
            } else {
                child.position = {crossAxisPosition, axisPosition};
            }

            axisPosition += axisChildSize + spacing;
        }

        return children;
    }
}

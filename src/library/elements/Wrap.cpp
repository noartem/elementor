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
        int spacing = this->spacing * ctx->monitorPixelScale;
        int crossSpacing = this->crossSpacing * ctx->monitorPixelScale;

        bool isRow = this->direction == WrapDirection::Row;
        int maxAxisSize = isRow ? boundaries.max.width : boundaries.max.height;
        int maxCrossAxisSize = isRow ? boundaries.max.height : boundaries.max.width;

        int axisPosition = 0;
        int crossAxisPosition = 0;

        int rowCrossAxisSize = 0;

        for (Element *childElement : this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, {{0, 0}, boundaries.max});

            int axisChildSize = isRow ? childSize.width : childSize.height;
            int crossAxisChildSize = isRow ? childSize.height : childSize.width;
            
            if (axisPosition + axisChildSize > maxAxisSize) {
                axisPosition = 0;
                crossAxisPosition += rowCrossAxisSize + crossSpacing;
            }

            if (crossAxisChildSize > rowCrossAxisSize) {
                rowCrossAxisSize = crossAxisChildSize;
            }

            axisPosition += axisChildSize + spacing;
        }

        int crossAxisSize = crossAxisPosition + rowCrossAxisSize;
        int width = isRow ? boundaries.max.width : crossAxisSize;
        int height = isRow ? crossAxisSize : boundaries.max.height;

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

        int spacing = this->getSpacing() * ctx->monitorPixelScale;
        int crossSpacing = this->getCrossSpacing() * ctx->monitorPixelScale;

        bool isRow = this->direction == WrapDirection::Row;

        int axisSize = isRow ? size.width : size.height;
        int crossAxisSize = isRow ? size.height : size.width;

        int axisPosition = 0;
        int crossAxisPosition = 0;

        int rowCrossAxisSize = 0;

        for (RenderElement &child : children) {
            int axisChildSize = isRow ? child.size.width : child.size.height;
            int crossAxisChildSize = isRow ? child.size.height : child.size.width;

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

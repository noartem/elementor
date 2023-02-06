//
// Created by noartem on 04.05.2022.
//

#include "Wrap.h"

namespace elementor::elements {
    std::shared_ptr<Wrap> wrap() {
        return std::make_shared<Wrap>();
    }

    std::shared_ptr<Wrap> Wrap::setSpacing(float spacing) {
        this->spacing = spacing;
        return shared_from_this();
    }

    float Wrap::getSpacing() const {
        return this->spacing;
    }

    std::shared_ptr<Wrap> Wrap::setCrossSpacing(float spacing) {
        this->crossSpacing = spacing;
        return shared_from_this();
    }

    float Wrap::getCrossSpacing() const {
        return this->crossSpacing;
    }

    std::shared_ptr<Wrap> Wrap::setSpacing(float spacing, float crossSpacing) {
        this->setSpacing(spacing);
        this->setCrossSpacing(crossSpacing);
        return shared_from_this();
    }

    std::shared_ptr<Wrap> Wrap::setDirection(WrapDirection direction) {
        this->direction = direction;
        return shared_from_this();
    }

    WrapDirection Wrap::getDirection() {
        return this->direction;
    }

    std::shared_ptr<Wrap> Wrap::appendChild(const std::shared_ptr<Element> &child) {
        this->addChild(child);
        return shared_from_this();
    }

    Size Wrap::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        float spacing = this->spacing * ctx->getPixelScale();
        float crossSpacing = this->crossSpacing * ctx->getPixelScale();

        bool isRow = this->direction == WrapDirection::Row;
        float maxAxisSize = isRow ? boundaries.max.width : boundaries.max.height;
        float maxCrossAxisSize = isRow ? boundaries.max.height : boundaries.max.width;

        float axisPosition = 0;
        float crossAxisPosition = 0;

        float rowCrossAxisSize = 0;

        for (const auto &childElement: this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, window, {{0, 0}, boundaries.max});

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

    std::vector<RenderElement>
    Wrap::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector<RenderElement> children;

        for (const auto &child: this->getChildrenList()) {
            RenderElement childElement;
            childElement.element = child;
            childElement.size = child->getSize(ctx, window, {{0, 0}, rect.size});
            children.push_back(childElement);
        }

        float spacing = this->getSpacing() * ctx->getPixelScale();
        float crossSpacing = this->getCrossSpacing() * ctx->getPixelScale();

        bool isRow = this->direction == WrapDirection::Row;

        float axisSize = isRow ? rect.size.width : rect.size.height;

        float axisPosition = 0;
        float crossAxisPosition = 0;

        float rowCrossAxisSize = 0;

        for (RenderElement &child: children) {
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

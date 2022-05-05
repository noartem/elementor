//
// Created by noartem on 04.05.2022.
//

#include "Wrap.h"

#include <iostream>

namespace elementor {
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
        child->context = this->context;
        this->addChild(child);
        return this;
    }

    std::vector <RenderElement> Wrap::getRenderChildren(RenderSize size) {
        std::vector <RenderElement> children;

        for (Element *childElement: this->getChildren()) {
            RenderElement child;
            child.element = childElement;
            child.element->context = this->context;
            child.size = childElement->getSize({{0, 0}, size});
            children.push_back(child);
        }

        int spacing = this->getSpacing() * this->context->monitorPixelScale;
        int crossSpacing = this->getCrossSpacing() * this->context->monitorPixelScale;

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
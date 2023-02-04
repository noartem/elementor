//
// Created by noartem on 13.04.2022.
//

#include "Row.h"

namespace elementor::elements {
    Row *row() {
        return new Row();
    }

    Row *Row::setSpacing(float spacing) {
        this->spacing = spacing;
        return this;
    }

    float Row::getSpacing() {
        return this->spacing;
    }

    Row *Row::appendChild(Element *child) {
        this->addChild(child);
        return this;
    }

    Size Row::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        float totalWidth = 0;
        float maxHeight = 0;
        for (Element *childElement : this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, window, {{0, 0}, boundaries.max});
            totalWidth += childSize.width;
            maxHeight = std::max(childSize.height, maxHeight);
        }

        totalWidth += (this->getChildrenSize() - 1) * this->getSpacing() * ctx->getPixelScale();

        return fitSizeInBoundaries({totalWidth, maxHeight}, boundaries);
    }

    std::vector <RenderElement> Row::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector <RenderElement> children;

        float spacing = this->getSpacing() * ctx->getPixelScale();

        float xPosition = 0;
        for (Element *child : this->getChildrenList()) {
            RenderElement childElement{};
            childElement.element = child;
            childElement.size = childElement.element->getSize(ctx, window, {{0, rect.size.height}, rect.size});

            childElement.position = {xPosition, 0};
            xPosition += childElement.size.width + spacing;

            children.push_back(childElement);
        }

        return children;
    }
}

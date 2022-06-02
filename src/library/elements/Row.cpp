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

    Size Row::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        int totalWidth = 0;
        for (Element *childElement : this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, {{0, boundaries.max.height}, boundaries.max});
            totalWidth += childSize.width;
        }

        totalWidth += (this->getChildrenSize() - 1) * ceil(this->getSpacing() * ctx->monitorPixelScale);

        return fitSizeInBoundaries({totalWidth, boundaries.max.height}, boundaries);
    }

    std::vector <RenderElement> Row::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        int spacing = ceil(this->getSpacing() * ctx->monitorPixelScale);

        int xPosition = 0;
        for (Element *childElement : this->getChildrenList()) {
            RenderElement child;
            child.element = childElement;
            child.size = child.element->getSize(ctx, {{0, size.height}, size});

            child.position = {xPosition, 0};
            xPosition += child.size.width + spacing;

            children.push_back(child);
        }

        return children;
    }
}

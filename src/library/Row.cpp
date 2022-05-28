//
// Created by noartem on 13.04.2022.
//

#include "Row.h"

namespace elementor {
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

    Row *Row::setAlignment(RowAlignment alignment) {
        this->alignment = alignment;
        return this;
    }

    RowAlignment Row::getAlignment() {
        return this->alignment;
    }

    Row *Row::appendChild(Element *child) {
        this->addChild(child);
        return this;
    }

    Size Row::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        int spacing = ceil(this->getSpacing() * ctx->monitorPixelScale);

        int maxHeight = 0;
        int totalWidth = 0;
        for (Element *childElement : this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, {{0, 0}, boundaries.max});
            maxHeight = std::max(childSize.height, maxHeight);
            totalWidth += childSize.width + spacing;
        }

        return fitSizeInBoundaries({totalWidth - spacing, maxHeight}, boundaries);
    }

    std::vector <RenderElement> Row::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        int spacing = ceil(this->getSpacing() * ctx->monitorPixelScale);

        int xPosition = 0;
        for (Element *childElement : this->getChildrenList()) {
            RenderElement child;
            child.element = childElement;
            child.size = child.element->getSize(ctx, {{0, 0}, size});

            child.position.x = xPosition;
            xPosition += child.size.width + spacing;

            if (this->getAlignment() == RowAlignment::Center) {
                child.position.y = (size.height - child.size.height) / 2;
            } else if (this->getAlignment() == RowAlignment::End) {
                child.position.y = size.height - child.size.height;
            } else {
                child.position.y = 0;
            }

            children.push_back(child);
        }

        return children;
    }
}

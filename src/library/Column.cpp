//
// Created by noartem on 13.04.2022.
//

#include "Column.h"

#include <climits>

namespace elementor {
    Column *column() {
        return new Column();
    }

    Column *Column::setSpacing(float spacing) {
        this->spacing = spacing;
        return this;
    }

    float Column::getSpacing() {
        return this->spacing;
    }

    Column *Column::setAlignment(ColumnAlignment alignment) {
        this->alignment = alignment;
        return this;
    }

    ColumnAlignment Column::getAlignment() {
        return this->alignment;
    }

    Column *Column::appendChild(Element *child) {
        this->addChild(child);
        return this;
    }

    Size Column::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        int spacing = ceil(this->getSpacing() * ctx->monitorPixelScale);

        int maxWidth = 0;
        int totalHeight = 0;
        for (Element *childElement : this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, {{0, 0}, {INT_MAX, INT_MAX}});
            maxWidth = std::max(childSize.width, maxWidth);
            totalHeight += childSize.height + spacing;
        }

        return fitSizeInBoundaries({maxWidth, totalHeight - spacing}, boundaries);
    }

    std::vector <RenderElement> Column::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        int spacing = ceil(this->getSpacing() * ctx->monitorPixelScale);

        int yPosition = 0;
        for (Element *childElement : this->getChildrenList()) {
            RenderElement child;
            child.element = childElement;
            child.size = child.element->getSize(ctx, {{0, 0}, {INT_MAX, INT_MAX}});

            child.position.y = yPosition;
            yPosition += child.size.height + spacing;

            if (this->getAlignment() == ColumnAlignment::Center) {
                child.position.x = (size.width - child.size.width) / 2;
            } else if (this->getAlignment() == ColumnAlignment::End) {
                child.position.x = size.width - child.size.width;
            } else {
                child.position.x = 0;
            }

            children.push_back(child);
        }

        return children;
    }
}

//
// Created by noartem on 13.04.2022.
//

#include "Column.h"

namespace elementor::elements {
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

    Column *Column::appendChild(Element *child) {
        this->addChild(child);
        return this;
    }

    Size Column::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        float maxWidth = 0;
        float totalHeight = 0;
        for (Element *childElement : this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, window, {{0, 0}, boundaries.max});
            maxWidth = std::max(childSize.width, maxWidth);
            totalHeight += childSize.height;
        }

        totalHeight += (this->getChildrenSize() - 1) * this->getSpacing() * window->getMonitorPixelScale();

        return fitSizeInBoundaries({maxWidth, totalHeight}, boundaries);
    }

    std::vector <RenderElement> Column::getChildren(ApplicationContext *ctx, Window *window, Size size) {
        std::vector <RenderElement> children;

        float spacing = this->getSpacing() * window->getMonitorPixelScale();

        float yPosition = 0;
        for (Element *childElement : this->getChildrenList()) {
            RenderElement child;
            child.element = childElement;
            child.size = child.element->getSize(ctx, window, {{size.width, 0}, size});

            child.position = {0, yPosition};
            yPosition += child.size.height + spacing;

            children.push_back(child);
        }

        return children;
    }
}

//
// Created by noartem on 13.04.2022.
//

#include "Row.h"

namespace elementor::elements {
    std::shared_ptr<Row> row() {
        return std::make_shared<Row>();
    }

    std::shared_ptr<Row> Row::setSpacing(float newSpacing) {
        this->spacing = newSpacing;
        return shared_from_this();
    }

    float Row::getSpacing() const {
        return this->spacing;
    }

    std::shared_ptr<Row> Row::appendChild(const std::shared_ptr<Element>& child) {
        this->addChild(child);
        return shared_from_this();
    }

    Size Row::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        float totalWidth = 0;
        float maxHeight = 0;
        for (const std::shared_ptr<Element>& childElement : this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, window, {{0, 0}, boundaries.max});
            totalWidth += childSize.width;
            maxHeight = std::max(childSize.height, maxHeight);
        }

        totalWidth += (this->getChildrenSize() - 1) * this->getSpacing() * ctx->getPixelScale();

        return fitSizeInBoundaries({totalWidth, maxHeight}, boundaries);
    }

    std::vector <RenderElement> Row::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector <RenderElement> children;

        float spacing = this->getSpacing() * ctx->getPixelScale();

        float xPosition = 0;
        for (const std::shared_ptr<Element>& child : this->getChildrenList()) {
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

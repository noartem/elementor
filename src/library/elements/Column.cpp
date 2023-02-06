//
// Created by noartem on 13.04.2022.
//

#include "Column.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<Column> column() {
        return std::make_shared<Column>();
    }

    std::shared_ptr<Column> Column::setSpacing(float newSpacing) {
        this->spacing = newSpacing;
        return shared_from_this();
    }

    float Column::getSpacing() const {
        return this->spacing;
    }

    std::shared_ptr<Column> Column::appendChild(const std::shared_ptr<Element>& child) {
        this->addChild(std::move(child));
        return shared_from_this();
    }

    Size
    Column::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        float maxWidth = 0;
        float totalHeight = 0;
        for (const std::shared_ptr<Element> &childElement: this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, window, {{0, 0}, boundaries.max});
            maxWidth = std::max(childSize.width, maxWidth);
            totalHeight += childSize.height;
        }

        totalHeight += (this->getChildrenSize() - 1) * this->getSpacing() * ctx->getPixelScale();

        return fitSizeInBoundaries({maxWidth, totalHeight}, boundaries);
    }

    std::vector<RenderElement>
    Column::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector<RenderElement> children;

        float spacing = this->getSpacing() * ctx->getPixelScale();

        float yPosition = 0;
        for (const std::shared_ptr<Element> &child: this->getChildrenList()) {
            RenderElement childElement{};
            childElement.element = child;
            childElement.size = child->getSize(ctx, window, {{rect.size.width, 0}, rect.size});

            childElement.position = {0, yPosition};
            yPosition += childElement.size.height + spacing;

            children.push_back(childElement);
        }

        return children;
    }
}

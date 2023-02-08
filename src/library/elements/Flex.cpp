//
// Created by noartem on 13.04.2022.
//

#include "Flex.h"
#include "Flexible.h"

#include <tuple>
#include <algorithm>
#include <utility>

namespace elementor::elements {
    std::shared_ptr<Flex> flex() {
        return std::make_shared<Flex>();
    }

    std::shared_ptr<Flex> Flex::setSpacing(float newSpacing) {
        this->spacing = newSpacing;
        return shared_from_this();
    }

    float Flex::getSpacing() const {
        return this->spacing;
    }

    std::shared_ptr<Flex> Flex::setDirection(FlexDirection newDirection) {
        this->direction = newDirection;
        return shared_from_this();
    }

    FlexDirection Flex::getDirection() {
        return this->direction;
    }

    std::shared_ptr<Flex> Flex::setAlignment(FlexAlignment newAlignment) {
        this->alignment = newAlignment;
        return shared_from_this();
    }

    FlexAlignment Flex::getAlignment() {
        return this->alignment;
    }

    std::shared_ptr<Flex> Flex::setCrossAlignment(FlexCrossAlignment newAlignment) {
        this->crossAlignment = newAlignment;
        return shared_from_this();
    }

    FlexCrossAlignment Flex::getCrossAlignment() {
        return this->crossAlignment;
    }

    std::shared_ptr<Flex> Flex::appendChild(const std::shared_ptr<Element>& child) {
        this->addChild(std::move(child));
        return shared_from_this();
    }

    Size Flex::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        if (this->alignment == FlexAlignment::Stretch) {
            return boundaries.max;
        }

        float maxCrossAxisSize = 0;
        for (const std::shared_ptr<Element>& childElement : this->getChildrenList()) {
            Size childSize = childElement->getSize(ctx, window, {{0, 0}, boundaries.max});
            float childCrossAxisSize = this->direction == FlexDirection::Row ? childSize.height : childSize.width;
            maxCrossAxisSize = std::max(childCrossAxisSize, maxCrossAxisSize);
        }

        Size size = {boundaries.max.width, boundaries.max.height};
        if (this->direction == FlexDirection::Row) {
            size.height = maxCrossAxisSize;
        } else {
            size.width = maxCrossAxisSize;
        }

        return fitSizeInBoundaries(size, boundaries);
    }

    std::vector <RenderElement> Flex::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector <RenderElement> children;

        Boundaries sizedChildBoundaries = {{0, 0}, rect.size};

        int childrenCount = this->getChildrenSize();
        float spacing = this->spacing * ctx->getPixelScale();
        float fixedSize = this->spacing * (childrenCount - 1);

        std::vector <std::tuple<int, int>> flexibleChildren;
        int flexibleGrowsSum = 0;

        for (int i = 0; i < childrenCount; i++) {
            RenderElement child;
            child.element = this->getChild(i);

            auto childFlexible = std::dynamic_pointer_cast<Flexible>(child.element);
            if (childFlexible) {
                float childGrow = childFlexible->getGrow();
                std::tuple<int, float> flexibleChild(i, childGrow);
                flexibleChildren.emplace_back(flexibleChild);
                flexibleGrowsSum += childGrow;
            } else {
                child.size = child.element->getSize(ctx, window, sizedChildBoundaries);
                fixedSize += this->direction == FlexDirection::Row ? child.size.width : child.size.height;
            }

            children.push_back(child);
        }

        float axisSize = this->direction == FlexDirection::Row ? rect.size.width : rect.size.height;
        float crossAxisSize = this->direction == FlexDirection::Row ? rect.size.height : rect.size.width;
        float freeSize = axisSize - fixedSize;
        float sizePerGrow = freeSize / std::max(flexibleGrowsSum, 1);

        for (std::tuple<int, int> flexibleChild: flexibleChildren) {
            int childIndex = std::get<0>(flexibleChild);
            RenderElement &child = children[childIndex];

            float childGrow = std::get<1>(flexibleChild);
            float childAxisSize = sizePerGrow * childGrow;

            if (this->direction == FlexDirection::Row) {
                child.size = {childAxisSize, rect.size.height};
            } else {
                child.size = {rect.size.width, childAxisSize};
            }
        }

        if (this->alignment == FlexAlignment::Stretch) {
            for (RenderElement &child: children) {
                if (this->direction == FlexDirection::Row) {
                    child.size.height = crossAxisSize;
                } else {
                    child.size.width = crossAxisSize;
                }
            }
        }

        float axisPosition = 0;

        if (flexibleGrowsSum == 0 && this->crossAlignment == FlexCrossAlignment::End) {
            axisPosition += freeSize;
        }

        if (flexibleGrowsSum == 0 && this->crossAlignment == FlexCrossAlignment::Center) {
            axisPosition += freeSize / 2;
        }

        float spaceBetween = freeSize / (childrenCount - 1);
        bool addSpaceEvenly = flexibleGrowsSum == 0 && this->crossAlignment == FlexCrossAlignment::SpaceEvenly;
        float spaceEvenly = freeSize / (childrenCount + 1);
        if (addSpaceEvenly) {
            axisPosition += spaceEvenly;
        }

        for (RenderElement &child: children) {
            float childAxisSize = this->direction == FlexDirection::Row ? child.size.width : child.size.height;
            float childCrossAxisSize = this->direction == FlexDirection::Row ? child.size.height : child.size.width;

            float crossAxisPosition = 0;
            if (this->alignment == FlexAlignment::End) {
                crossAxisPosition = crossAxisSize - childCrossAxisSize;
            } else if (this->alignment == FlexAlignment::Center) {
                crossAxisPosition = (crossAxisSize - childCrossAxisSize) / 2;
            }

            if (this->direction == FlexDirection::Row) {
                child.position = {axisPosition, crossAxisPosition};
            } else {
                child.position = {crossAxisPosition, axisPosition};
            }

            axisPosition += this->spacing;
            axisPosition += childAxisSize;

            if (addSpaceEvenly) {
                axisPosition += spaceEvenly;
            }

            if (flexibleGrowsSum == 0 && this->crossAlignment == FlexCrossAlignment::SpaceBetween) {
                axisPosition += spaceBetween;
            }
        }

        return children;
    }
}

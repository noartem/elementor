//
// Created by noartem on 13.04.2022.
//

#include "Flex.h"
#include "Flexible.h"

#include <tuple>
#include <algorithm>

namespace elementor {
    Flex *flex() {
        return new Flex();
    }

    Flex *Flex::setSpacing(float spacing) {
        this->spacing = spacing;
        return this;
    }

    float Flex::getSpacing() {
        return this->spacing;
    }

    Flex *Flex::setDirection(FlexDirection direction) {
        this->direction = direction;
        return this;
    }

    FlexDirection Flex::getDirection() {
        return this->direction;
    }

    Flex *Flex::setAlignment(FlexAlignment alignment) {
        this->alignment = alignment;
        return this;
    }

    FlexAlignment Flex::getAlignment() {
        return this->alignment;
    }

    Flex *Flex::setCrossAlignment(FlexCrossAlignment alignment) {
        this->crossAlignment = alignment;
        return this;
    }

    FlexCrossAlignment Flex::getCrossAlignment() {
        return this->crossAlignment;
    }

    Flex *Flex::appendChild(Element *child) {
        this->addChild(child);
        return this;
    }

    std::vector <RenderElement> Flex::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        Boundaries sizedChildBoundaries = {{0, 0}, size};

        int childrenCount = this->getChildrenSize();
        int spacing = ceil(this->spacing * ctx->monitorPixelScale);
        int fixedSize = this->spacing * (childrenCount - 1);

        std::vector <std::tuple<int, int>> flexibleChildren;
        int flexibleGrowsSum = 0;

        for (int i = 0; i < childrenCount; i++) {
            RenderElement child;
            child.element = this->getChild(i);

            Flexible *childFlexible = dynamic_cast<Flexible *>(child.element);

            if (childFlexible == NULL) {
                child.size = child.element->getSize(ctx, sizedChildBoundaries);
                fixedSize += this->direction == FlexDirection::Row ? child.size.width : child.size.height;
            } else {
                int childGrow = childFlexible->getGrow();
                std::tuple<int, int> flexibleChild(i, childGrow);
                flexibleChildren.push_back(flexibleChild);
                flexibleGrowsSum += childGrow;
            }

            children.push_back(child);
        }

        int axisSize = this->direction == FlexDirection::Row ? size.width : size.height;
        int crossAxisSize = this->direction == FlexDirection::Row ? size.height : size.width;
        int freeSize = axisSize - fixedSize;
        int sizePerGrow = freeSize / std::max(flexibleGrowsSum, 1);

        for (std::tuple<int, int> flexibleChild: flexibleChildren) {
            int childIndex = std::get<0>(flexibleChild);
            RenderElement &child = children[childIndex];

            int childGrow = std::get<1>(flexibleChild);
            int axisSize = sizePerGrow * childGrow;
            Boundaries childBoundaries;
            if (this->direction == FlexDirection::Row) {
                childBoundaries = {{axisSize, 0}, {axisSize, size.height}};
            } else {
                childBoundaries = {{0, axisSize}, {size.width, axisSize}};
            }

            child.size = child.element->getSize(ctx, childBoundaries);
        }

        int axisPosition = 0;

        if (flexibleGrowsSum == 0 && this->crossAlignment == FlexCrossAlignment::End) {
            axisPosition += freeSize;
        }

        int addSpaceEvenly = flexibleGrowsSum == 0 && this->crossAlignment == FlexCrossAlignment::SpaceEvenly;
        int spaceEvenly = freeSize / (childrenCount + 1);
        if (addSpaceEvenly) {
            axisPosition += spaceEvenly;
        }

        for (RenderElement &child: children) {
            int childAxisSize = this->direction == FlexDirection::Row ? child.size.width : child.size.height;
            int childCrossAxisSize = this->direction == FlexDirection::Row ? child.size.height : child.size.width;

            int crossAxisPosition = 0;
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
                axisPosition += freeSize;
            }
        }

        return children;
    }
}

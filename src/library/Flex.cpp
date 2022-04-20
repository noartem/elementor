//
// Created by noartem on 13.04.2022.
//

#include "Flex.h"
#include "Flexible.h"

#include <tuple>
#include <algorithm>

namespace elementor {
    std::shared_ptr <ElementRenderer> Flex::render() {
        auto renderer = std::make_shared<FlexRenderer>();
        renderer->spacing = this->spacing;
        renderer->direction = this->direction;
        renderer->alignment = this->alignment;
        renderer->crossAlignment = this->crossAlignment;
        renderer->children = this->children;
        return renderer;
    }

    std::vector <RenderElement> FlexRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        RenderBoundaries sizedChildBoundaries = {{0, 0}, size};

        int childrenCount = this->children.size();
        int fixedSize = this->spacing * (childrenCount - 1);

        std::vector <std::tuple<int, int>> flexibleChildren;
        int flexibleGrowsSum = 0;

        for (int i = 0; i < childrenCount; i++) {
            RenderElement child;
            child.element = this->children[i];
            child.renderer = child.element->render();

            Flexible *childAsFlexible = dynamic_cast<Flexible *>(child.element);
            if (childAsFlexible) {
                std::tuple<int, int> flexibleChild(i, childAsFlexible->grow);
                flexibleChildren.push_back(flexibleChild);
                flexibleGrowsSum += childAsFlexible->grow;
            } else {
                child.size = child.renderer->getSize(sizedChildBoundaries);
                fixedSize += this->direction == FlexDirection::Row ? child.size.width : child.size.height;
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
            RenderBoundaries childBoundaries;
            if (this->direction == FlexDirection::Row) {
                childBoundaries = {{axisSize, 0},
                                   {axisSize, size.height}};
            } else {
                childBoundaries = {{0,          axisSize},
                                   {size.width, axisSize}};
            }

            child.size = child.renderer->getSize(childBoundaries);
        }

        int axisPosition = 0;

        if (flexibleGrowsSum == 0 && this->crossAlignment == FlexCrossAlignment::End) {
            axisPosition += freeSize;
        }

        int addSpaceBetween = flexibleGrowsSum == 0 && this->crossAlignment == FlexCrossAlignment::SpaceBetween;
        int spaceBetween = freeSize / (childrenCount + 1);
        if (addSpaceBetween) {
            axisPosition += spaceBetween;
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

            if (addSpaceBetween) {
                axisPosition += spaceBetween;
            }
        }

        return children;
    }
}

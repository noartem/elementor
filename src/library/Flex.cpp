//
// Created by noartem on 13.04.2022.
//

#include "Flex.h"
#include "Flexible.h"
#include "Expanded.h"

#include <tuple>
#include <algorithm>

namespace elementor {
    Flex::Flex(std::vector<Element *> children) {
        this->setChildren(children);
    }

    Flex::Flex(FlexDirection direction, std::vector<Element *> children) {
        this->setDirection(direction);
        this->setChildren(children);
    }

    Flex::Flex(FlexAlignment alignment, std::vector<Element *> children) {
        this->setAlignment(alignment);
        this->setChildren(children);
    }

    Flex::Flex(FlexCrossAlignment crossAlignment, std::vector<Element *> children) {
        this->setCrossAlignment(crossAlignment);
        this->setChildren(children);
    }

    Flex::Flex(FlexAlignment alignment, FlexCrossAlignment crossAlignment, std::vector<Element *> children) {
        this->setAlignment(alignment);
        this->setCrossAlignment(crossAlignment);
        this->setChildren(children);
    }

    Flex::Flex(FlexDirection direction, FlexAlignment alignment, std::vector<Element *> children) {
        this->setDirection(direction);
        this->setAlignment(alignment);
        this->setChildren(children);
    }

    Flex::Flex(FlexDirection direction, FlexCrossAlignment crossAlignment, std::vector<Element *> children) {
        this->setDirection(direction);
        this->setCrossAlignment(crossAlignment);
        this->setChildren(children);
    }

    Flex::Flex(FlexDirection direction, FlexAlignment alignment, FlexCrossAlignment crossAlignment, std::vector<Element *> children) {
        this->setDirection(direction);
        this->setAlignment(alignment);
        this->setCrossAlignment(crossAlignment);
        this->setChildren(children);
    }

    Flex::Flex(float spacing, std::vector<Element *> children) {
        this->setSpacing(spacing);
        this->setChildren(children);
    }

    Flex::Flex(float spacing, FlexDirection direction, std::vector<Element *> children) {
        this->setSpacing(spacing);
        this->setDirection(direction);
        this->setChildren(children);
    }

    Flex::Flex(float spacing, FlexAlignment alignment, std::vector<Element *> children) {
        this->setSpacing(spacing);
        this->setAlignment(alignment);
        this->setChildren(children);
    }

    Flex::Flex(float spacing, FlexDirection direction, FlexAlignment alignment, std::vector<Element *> children) {
        this->setSpacing(spacing);
        this->setDirection(direction);
        this->setAlignment(alignment);
        this->setChildren(children);
    }

    Flex::Flex(float spacing, FlexCrossAlignment crossAlignment, std::vector<Element *> children) {
        this->setSpacing(spacing);
        this->setCrossAlignment(crossAlignment);
        this->setChildren(children);
    }

    Flex::Flex(float spacing, FlexDirection direction, FlexCrossAlignment crossAlignment, std::vector<Element *> children) {
        this->setSpacing(spacing);
        this->setDirection(direction);
        this->setCrossAlignment(crossAlignment);
        this->setChildren(children);
    }

    Flex::Flex(float spacing, FlexAlignment alignment, FlexCrossAlignment crossAlignment, std::vector<Element *> children) {
        this->setSpacing(spacing);
        this->setAlignment(alignment);
        this->setCrossAlignment(crossAlignment);
        this->setChildren(children);
    }

    Flex::Flex(float spacing, FlexDirection direction, FlexAlignment alignment, FlexCrossAlignment crossAlignment, std::vector<Element *> children) {
        this->setSpacing(spacing);
        this->setDirection(direction);
        this->setAlignment(alignment);
        this->setCrossAlignment(crossAlignment);
        this->setChildren(children);
    }

    void Flex::setSpacing(float spacing) {
        this->spacing = spacing;
    }

    float Flex::getSpacing() {
        return this->spacing;
    }

    void Flex::setDirection(FlexDirection direction) {
        this->direction = direction;
    }

    FlexDirection Flex::getDirection() {
        return this->direction;
    }

    void Flex::setAlignment(FlexAlignment alignment) {
        this->alignment = alignment;
    }

    FlexAlignment Flex::getAlignment() {
        return this->alignment;
    }

    void Flex::setCrossAlignment(FlexCrossAlignment alignment) {
        this->crossAlignment = alignment;
    }

    FlexCrossAlignment Flex::getCrossAlignment() {
        return this->crossAlignment;
    }

    std::shared_ptr <ElementRenderer> Flex::render() {
        return std::make_shared<FlexRenderer>(this->context, this->spacing, this->direction, this->alignment, this->crossAlignment, this->getChildren());
    }

    bool isFlexible(Element *element) {
        return (
            dynamic_cast<Flexible *>(element) != NULL ||
            dynamic_cast<Expanded *>(element) != NULL
        );
    }

    int getFlexibleGrow(Element *element) {
        if (dynamic_cast<Flexible *>(element)) {
            return dynamic_cast<Flexible *>(element)->getGrow();
        } else if (dynamic_cast<Expanded *>(element)) {
            return dynamic_cast<Expanded *>(element)->getGrow();
        } else {
            return 0;
        }
    }

    FlexRenderer::FlexRenderer(ApplicationContext *context, float spacing, FlexDirection direction, FlexAlignment alignment, FlexCrossAlignment crossAlignment, std::vector<Element *> children) {
        this->context = context;
        this->spacing = spacing * this->context->monitorPixelScale;
        this->direction = direction;
        this->alignment = alignment;
        this->crossAlignment = crossAlignment;
        this->children = children;
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
            child.element->context = this->context;
            child.renderer = child.element->render();

            if (isFlexible(child.element)) {
                int childGrow = getFlexibleGrow(child.element);
                std::tuple<int, int> flexibleChild(i, childGrow);
                flexibleChildren.push_back(flexibleChild);
                flexibleGrowsSum += childGrow;
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

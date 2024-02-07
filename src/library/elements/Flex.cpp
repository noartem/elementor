//
// Created by noartem on 13.04.2022.
//

#include "Flex.h"
#include "Flexible.h"

namespace elementor::elements {
	Size Flex::getSize(const Boundaries& boundaries) {
		float minWidth =
			alignment == FlexAlignment::Stretch && direction == FlexDirection::Column ? boundaries.max.width : 0;
		float minHeight =
			alignment == FlexAlignment::Stretch && direction == FlexDirection::Row ? boundaries.max.height : 0;
		Size minSize = { .width = minWidth, .height = minHeight };

		Boundaries childBoundaries = { .min = minSize, .max = boundaries.max };

		float totalAxisSize = 0;
		float maxCrossAxisSize = 0;
		bool hasFlexibleChildren = false;

		for (const auto& child: this->getChildrenList()) {
			Size childSize = child->getSize(childBoundaries);

			float childCrossAxisSize = this->direction == FlexDirection::Row ? childSize.height : childSize.width;
			float childAxisSize = this->direction == FlexDirection::Row ? childSize.width : childSize.height;

			maxCrossAxisSize = std::max(childCrossAxisSize, maxCrossAxisSize);
			totalAxisSize += childAxisSize;

			auto childFlexible = std::dynamic_pointer_cast<Flexible>(child);
			if (childFlexible) {
				hasFlexibleChildren = true;
			}
		}

		auto pixelScale = ctx->getPixelScale();
		float spacingScaled = spacing * pixelScale;
		totalAxisSize += ((float)children.size() - 1) * spacingScaled;

		float maxAxisSize = this->direction == FlexDirection::Row ? boundaries.max.width : boundaries.max.height;
		float axisSize = hasFlexibleChildren ? maxAxisSize : totalAxisSize;

		float width = this->direction == FlexDirection::Row ? axisSize : maxCrossAxisSize;
		float height = this->direction == FlexDirection::Row ? maxCrossAxisSize : axisSize;

		Size size = { width, height };
		size = fitSizeInBoundaries(size, boundaries);

		return size;
	}

	std::vector<ElementWithRect> Flex::getChildren(const ElementRect& rect) {
		std::vector<ElementWithRect> childrenElements;

		float minWidth = alignment == FlexAlignment::Stretch && direction == FlexDirection::Column
						 ? rect.size.width : 0;
		float minHeight = alignment == FlexAlignment::Stretch && direction == FlexDirection::Row
						  ? rect.size.height : 0;
		Size minSize = { .width = minWidth, .height = minHeight };

		Boundaries sizedChildBoundaries = { .min = minSize, .max = rect.size };

		auto pixelScale = ctx->getPixelScale();
		float spacingScaled = spacing * pixelScale;

		std::vector<std::tuple<int, float>> flexibleChildren;
		float flexibleGrowsSum = 0;
		float fixedSize = spacingScaled * ((float)children.size() - 1);

		for (int i = 0; i < children.size(); i++) {
			const auto& child = children[i];

			auto childFlexible = std::dynamic_pointer_cast<Flexible>(child);
			if (childFlexible) {
				float childGrow = childFlexible->getGrow();
				flexibleGrowsSum += childGrow;

				std::tuple<int, float> flexibleChild(i, childGrow);
				flexibleChildren.emplace_back(flexibleChild);

				ElementWithRect childElement(child, { .size = { 0, 0 }, .position = { 0, 0 }});
				childrenElements.push_back(childElement);
				continue;
			}

			Size childSize = child->getSize(sizedChildBoundaries);
			Rect childRect = {
				.size = childSize,
				.position = { .x = 0, .y = 0 }
			};

			ElementWithRect childElement(child, childRect);
			childrenElements.push_back(childElement);

			auto childAxisSize = direction == FlexDirection::Row ? childSize.width : childSize.height;
			fixedSize += childAxisSize;
		}

		float axisSize = direction == FlexDirection::Row ? rect.size.width : rect.size.height;
		float crossAxisSize = direction == FlexDirection::Row ? rect.size.height : rect.size.width;
		float freeSize = axisSize - fixedSize;
		float sizePerGrow = freeSize / std::max(flexibleGrowsSum, 1.0f);

		for (auto flexibleChild: flexibleChildren) {
			int childIndex = std::get<0>(flexibleChild);
			auto& childElement = childrenElements[childIndex];
			auto child = std::get<0>(childElement);
			auto& childRect = std::get<1>(childElement);

			float childGrow = std::get<1>(flexibleChild);
			float childAxisSize = sizePerGrow * childGrow;

			float childMinWidth = direction == FlexDirection::Row ? childAxisSize : 0;
			float childMaxWidth = direction == FlexDirection::Row ? std::min(childAxisSize, rect.size.width) : rect.size.width;
			float childMinHeight = direction == FlexDirection::Column ? childAxisSize : 0;
			float childMaxHeight = direction == FlexDirection::Column ? std::min(childAxisSize, rect.size.height) : rect.size.height;
			Boundaries childBoundaries = {
				.min = { .width = std::max(minWidth, childMinWidth), .height = std::max(minHeight, childMinHeight) },
				.max = { .width = childMaxWidth, .height = childMaxHeight },
			};

			childRect.size = child->getSize(childBoundaries);
		}

		float axisPosition = 0;

		if (flexibleGrowsSum == 0 && crossAlignment == FlexCrossAlignment::End) {
			axisPosition += freeSize;
		}

		if (flexibleGrowsSum == 0 && crossAlignment == FlexCrossAlignment::Center) {
			axisPosition += freeSize / 2;
		}

		float spaceBetween = (flexibleGrowsSum == 0 && this->crossAlignment == FlexCrossAlignment::SpaceBetween)
							 ? freeSize / (children.size() - 1)
							 : 0;

		float spaceEvenly = (flexibleGrowsSum == 0 && this->crossAlignment == FlexCrossAlignment::SpaceEvenly)
							? freeSize / (children.size() + 1)
							: 0;
		axisPosition += spaceEvenly;

		for (auto& childElement: childrenElements) {
			const auto& child = std::get<0>(childElement);
			auto& childRect = std::get<1>(childElement);
			auto& childSize = childRect.size;

			float childAxisSize = direction == FlexDirection::Row ? childSize.width : childSize.height;
			float childCrossAxisSize = direction == FlexDirection::Row ? childSize.height : childSize.width;

			float crossAxisPosition = 0;
			if (this->alignment == FlexAlignment::End) {
				crossAxisPosition = crossAxisSize - childCrossAxisSize;
			}
			if (this->alignment == FlexAlignment::Center) {
				crossAxisPosition = (crossAxisSize - childCrossAxisSize) / 2;
			}

			if (this->direction == FlexDirection::Row) {
				childRect.position = { axisPosition, crossAxisPosition };
			}
			if (this->direction == FlexDirection::Column) {
				childRect.position = { crossAxisPosition, axisPosition };
			}

			axisPosition += spacingScaled;
			axisPosition += childAxisSize;
			axisPosition += spaceEvenly;
			axisPosition += spaceBetween;
		}

		return childrenElements;
	}
}

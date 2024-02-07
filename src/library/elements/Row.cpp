//
// Created by noartem on 13.04.2022.
//

#include "Row.h"

namespace elementor::elements {
	Size Row::getSize(const Boundaries& boundaries) {
		float maxHeight = 0;
		float totalWidth = 0;
		for (const auto& childElement: children) {
			Boundaries childBoundaries = {
				.min = { .width = 0, .height = boundaries.min.height },
				.max = boundaries.max
			};
			Size childSize = childElement->getSize(childBoundaries);

			maxHeight = std::max(childSize.height, maxHeight);
			totalWidth += childSize.width;
		}

		auto pixelScale = ctx->getPixelScale();
		auto spacingScaled = spacing * pixelScale;

		totalWidth += ((float)children.size() - 1) * spacingScaled;

		Size elementSize = {
			.width = totalWidth,
			.height = maxHeight,
		};
		elementSize = fitSizeInBoundaries(elementSize, boundaries);

		return elementSize;
	}

	std::vector <ElementWithRect> Row::getChildren(const ElementRect& rect) {
		std::vector <ElementWithRect> childrenElements;

		auto pixelScale = ctx->getPixelScale();
		auto spacingScaled = spacing * pixelScale;

		float xPosition = 0;
		for (const auto& child: children) {
			Boundaries childBoundaries = {
				.min = { .width = 0, .height = rect.size.height },
				.max = rect.size
			};
			Size childSize = child->getSize(childBoundaries);

			Rect childRect = {
				.size = child->getSize(childBoundaries),
				.position = {
					.x = xPosition,
					.y = 0,
				}
			};

			ElementWithRect childElement(child, childRect);
			childrenElements.push_back(childElement);

			xPosition += childSize.width;
			xPosition += spacingScaled;
		}

		return childrenElements;
	}
}

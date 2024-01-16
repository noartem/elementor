//
// Created by noartem on 13.04.2022.
//

#include "Column.h"

namespace elementor::elements {
	Size Column::getSize(const Boundaries& boundaries) {
		float maxWidth = 0;
		float totalHeight = 0;
		for (const auto& childElement: children) {
			Boundaries childBoundaries = {
				.min = { .width = boundaries.min.width, .height = 0 },
				.max = boundaries.max
			};
			Size childSize = childElement->getSize(childBoundaries);

			maxWidth = std::max(childSize.width, maxWidth);
			totalHeight += childSize.height;
		}

		auto pixelScale = ctx->getWindowCtx()->getPixelScale();
		auto spacingScaled = spacing * pixelScale;

		totalHeight += ((float)children.size() - 1) * spacingScaled;

		Size elementSize = {
			.width = maxWidth,
			.height = totalHeight,
		};
		elementSize = fitSizeInBoundaries(elementSize, boundaries);

		return elementSize;
	}

	std::vector<ElementWithRect> Column::getChildren(const ElementRect& rect) {
		std::vector<ElementWithRect> childrenElements;

		auto pixelScale = ctx->getWindowCtx()->getPixelScale();
		auto spacingScaled = spacing * pixelScale;

		float yPosition = 0;
		for (const auto& child: children) {
			Boundaries childBoundaries = {
				.min = { .width = rect.size.width, .height = 0 },
				.max = rect.size
			};
			Size childSize = child->getSize(childBoundaries);

			Rect childRect = {
				.size = childSize,
				.position = {
					.x = 0,
					.y = yPosition,
				}
			};

			ElementWithRect childElement(child, childRect);
			childrenElements.push_back(childElement);

			yPosition += childSize.height;
			yPosition += spacingScaled;
		}

		return childrenElements;
	}
}

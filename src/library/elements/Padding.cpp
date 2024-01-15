//
// Created by noartem on 13.04.2022.
//

#include "Padding.h"

namespace elementor::elements {

	Size Padding::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		auto pixelScale = ctx->getWindowCtx()->getPixelScale();
		float paddingTop = paddings.top * pixelScale;
		float paddingBottom = paddings.bottom * pixelScale;
		float paddingY = paddingTop + paddingBottom;
		float paddingRight = paddings.right * pixelScale;
		float paddingLeft = paddings.left * pixelScale;
		float paddingX = paddingLeft + paddingRight;

		Boundaries childBoundaries = {
			.min = {
				.width = std::max(boundaries.min.width - paddingX, 0.0f),
				.height = std::max(boundaries.min.height - paddingY, 0.0f)
			},
			.max = {
				.width = std::max(boundaries.max.width - paddingX, 0.0f),
				.height = std::max(boundaries.max.height - paddingY, 0.0f)
			}
		};
		Size childSize = child->getSize(childBoundaries);

		Size elementSize = {
			.width = childSize.width + paddingX,
			.height = childSize.height + paddingY
		};
		elementSize = fitSizeInBoundaries(elementSize, boundaries);

		return elementSize;
	}

	std::vector<ElementWithRect> Padding::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		auto pixelScale = ctx->getWindowCtx()->getPixelScale();
		float paddingTop = paddings.top * pixelScale;
		float paddingBottom = paddings.bottom * pixelScale;
		float paddingY = paddingTop + paddingBottom;
		float paddingRight = paddings.right * pixelScale;
		float paddingLeft = paddings.left * pixelScale;
		float paddingX = paddingLeft + paddingRight;

		Rect childRect = {
			.size = {
				.width = rect.size.width - paddingX,
				.height = rect.size.height - paddingY,
			},
			.position = {
				.x = paddingLeft,
				.y = paddingTop
			},
		};

		ElementWithRect childElementWithRect(child, childRect);
		return { childElementWithRect };
	}
}

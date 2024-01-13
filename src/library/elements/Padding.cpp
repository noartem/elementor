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

		childSize.width += paddingX;
		childSize.height += paddingY;
		childSize = fitSizeInBoundaries(childSize, boundaries);

		return childSize;
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
		float paddingX = paddingRight + paddingLeft;

		Boundaries childBoundaries = {
				.min = { .width = 0.0f, .height = 0.0f },
				.max = {
						.width = std::max(rect.size.width - paddingX, 0.0f),
						.height = std::max(rect.size.height - paddingY, 0.0f)
				}
		};

		Rect childRect = {
				.size = child->getSize(childBoundaries),
				.position = {
						.x = paddingLeft,
						.y = paddingTop
				},
		};

		ElementWithRect childElementWithRect(child, childRect);
		return { childElementWithRect };
	}
}

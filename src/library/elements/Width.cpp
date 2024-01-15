//
// Created by noartem on 13.04.2022.
//

#include "Width.h"

namespace elementor::elements {
	Size Width::getSize(const Boundaries& boundaries) {
		float pixelScale = ctx->getWindowCtx()->getPixelScale();
		float widthScaled = width * pixelScale;

		if (doesNotHaveChild()) {
			return fitSizeInBoundaries({
				.width = widthScaled,
				.height = boundaries.max.height
			}, boundaries);
		}

		Boundaries childBoundaries = {
			.min = {
				.width = std::max(widthScaled, boundaries.min.width),
				.height = boundaries.min.height,
			},
			.max = {
				.width = std::min(widthScaled, boundaries.max.width),
				.height = boundaries.max.height,
			}
		};

		return child->getSize(childBoundaries);
	}

	std::vector<ElementWithRect> Width::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Rect childRect = {
			.size = rect.size,
			.position = { .x = 0, .y = 0 },
		};

		ElementWithRect childElement(child, childRect);
		return { childElement };
	}
}

//
// Created by noartem on 13.04.2022.
//

#include "Height.h"

namespace elementor::elements {
	Size Height::getSize(const Boundaries& boundaries) {
		float pixelScale = ctx->getWindowCtx()->getPixelScale();
		float heightScaled = height * pixelScale;

		if (doesNotHaveChild()) {
			return fitSizeInBoundaries({
					.width = boundaries.max.width,
					.height = height
			}, boundaries);
		}

		return child->getSize({
				.min = {
						.width = boundaries.min.width,
						.height = std::max(heightScaled, boundaries.min.height)
				},
				.max = {
						.width = boundaries.max.width,
						.height = std::min(heightScaled, boundaries.max.height)
				}
		});
	}

	std::vector<ElementWithRect> Height::getChildren(const ElementRect& rect) {
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

//
// Created by noartem on 13.04.2022.
//

#include "Ratio.h"

namespace elementor::elements {
	Size fitRatioWithin(float ratio, const Size& size) {
		if (ratio >= 1) {
			return {
				.width = size.width,
				.height = size.width / ratio
			};
		} else {
			return {
				.width = size.height * ratio,
				.height = size.height
			};
		}
	}

	Size Ratio::getSize(const Boundaries& boundaries) {
		return fitSizeInBoundaries(fitRatioWithin(ratio, boundaries.max), boundaries);
	}

	std::vector<ElementWithRect> Ratio::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Size childSize = fitRatioWithin(ratio, rect.size);

		Position childPosition = {
			.x = (rect.size.width - childSize.width) / 2,
			.y = (rect.size.height - childSize.height) / 2
		};

		Rect childRect = { .size = childSize, .position = childPosition };

		ElementWithRect childElement(child, childRect);
		return { childElement };
	}
}

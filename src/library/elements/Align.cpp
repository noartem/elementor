//
// Created by noartem on 29.05.2022.
//

#include "Align.h"

namespace elementor::elements {
	Size Align::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		Boundaries childBoundaries = {
			.min = { 0, 0 },
			.max = boundaries.max
		};
		Size childSize = child->getSize(childBoundaries);

		Boundaries elementBoundaries = {
			.min = {
				.width = widthCoefficient.has_value() ? boundaries.max.width : boundaries.min.width,
				.height = heightCoefficient.has_value() ? boundaries.max.height : boundaries.min.height
			},
			.max = boundaries.max
		};
		Size elementSize = fitSizeInBoundaries(childSize, elementBoundaries);

		return elementSize;
	}

	std::vector<ElementWithRect> Align::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Boundaries childBoundaries = {
			.min = { rect.size.width, 0 },
			.max = rect.size,
		};
		Size childSize = child->getSize(childBoundaries);

		Position childPosition = {
			.x = rect.size.width * widthCoefficient.value_or(0) -
				childSize.width * widthChildCoefficient.value_or(widthCoefficient.value_or(0)),
			.y = rect.size.height * heightCoefficient.value_or(0) -
				childSize.height * heightChildCoefficient.value_or(heightCoefficient.value_or(0))
		};

		Rect childRect = { .size = childSize, .position = childPosition };

		ElementWithRect childElement(child, childRect);
		return { childElement };
	}
}

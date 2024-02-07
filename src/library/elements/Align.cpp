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
			.min = {
				widthCoefficient.has_value() ? 0 : boundaries.min.width,
				heightCoefficient.has_value() ? 0 : boundaries.min.height,
			},
			.max = boundaries.max
		};

		Size childSize = child->getSize(childBoundaries);
		Size elementSize = fitSizeInBoundaries(childSize, boundaries);

		return elementSize;
	}

	std::vector <ElementWithRect> Align::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Boundaries childBoundaries = {
			.min = {
				.width = widthCoefficient.has_value() ? 0 : rect.size.width,
				.height = heightCoefficient.has_value() ? 0 : rect.size.height,
			},
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

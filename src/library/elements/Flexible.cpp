//
// Created by noartem on 13.04.2022.
//

#include "Flexible.h"

namespace elementor::elements {
	Size Flexible::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		return child->getSize(boundaries);
	}

	std::vector<ElementWithRect> Flexible::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Rect childRect = {
			.size = rect.size,
			.position = { 0, 0 }
		};
		ElementWithRect childElement(child, childRect);
		return { childElement };
	}
}

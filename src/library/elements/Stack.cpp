//
// Created by noartem on 03.02.2022.
//

#include "Stack.h"

namespace elementor::elements {
	Size Stack::getSize(const Boundaries& boundaries) {
		Size size{ 0, 0 };
		for (const auto& child: children) {
			Size childSize = child->getSize(boundaries);
			size.width = std::max(size.height, childSize.width);
			size.height = std::max(size.height, childSize.height);
		}
		return fitSizeInBoundaries(size, boundaries);
	}

	std::vector <ElementWithRect> Stack::getChildren(const ElementRect& rect) {
		std::vector <ElementWithRect> childrenElements;

		Boundaries childBoundaries = {
			.min = ZeroSize,
			.max = rect.size
		};

		for (const auto& child: children) {
			Size childSize = child->getSize(childBoundaries);

			Rect childRect = {
				.size = childSize,
				.position = { .x = 0, .y = 0 }
			};

			ElementWithRect childElement(child, childRect);
			childrenElements.push_back(childElement);
		}

		return childrenElements;
	}
}

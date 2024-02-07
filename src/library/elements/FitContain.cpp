//
// Created by noartem on 27.07.2022.
//

#include "FitContain.h"

#include <utility>

namespace elementor::elements {
	Size fitSizeWithin(const Size& inner, const Size& outer) {
		float innerRatio = inner.width / inner.height;
		float outerRatio = outer.width / outer.height;
		float resizeFactor = (innerRatio >= outerRatio)
							 ? (outer.width / inner.width)
							 : (outer.height / inner.height);

		return {
			.width = inner.width * resizeFactor,
			.height = inner.height * resizeFactor
		};
	}

	std::vector <ElementWithRect> FitContain::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Size realChildSize = child->getSize(InfiniteBoundaries);
		Size childSize = fitSizeWithin(realChildSize, rect.size);

		Position childPosition = {
			.x = (rect.size.width - childSize.width) / 2,
			.y = (rect.size.height - childSize.height) / 2
		};

		Rect childRect = { .size = childSize, .position = childPosition };

		ElementWithRect childElement(child, childRect);
		return { childElement };
	}
}

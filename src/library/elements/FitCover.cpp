//
// Created by noartem on 27.07.2022.
//

#include "FitCover.h"

#include <utility>

namespace elementor::elements {
	std::vector<ElementWithRect> FitCover::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Size realChildSize = child->getSize(InfiniteBoundaries);

		float ratio = realChildSize.width / realChildSize.height;
		Size childSize{
			.width = rect.size.width > rect.size.height ? rect.size.width : rect.size.height / ratio,
			.height = rect.size.width > rect.size.height ? rect.size.width / ratio : rect.size.height,
		};

		Position childPosition = {
			.x = (rect.size.width - childSize.width) / 2,
			.y = (rect.size.height - childSize.height) / 2
		};

		Rect childRect = { .size = childSize, .position = childPosition };

		ElementWithRect childElement(child, childRect);
		return { childElement };
	}
}

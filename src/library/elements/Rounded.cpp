//
// Created by noartem on 21.04.2022.
//

#include "Rounded.h"

#include <include/core/SkRRect.h>

namespace elementor::elements {
	void Rounded::paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		auto pixelScale = ctx->getPixelScale();

		float topLeft = rectRadius.topLeft * pixelScale;
		float topRight = rectRadius.topRight * pixelScale;
		float bottomRight = rectRadius.bottomRight * pixelScale;
		float bottomLeft = rectRadius.bottomLeft * pixelScale;

		SkVector corners[] = {{ topLeft, topLeft },
							  { topRight, topRight },
							  { bottomRight, bottomRight },
							  { bottomLeft, bottomLeft }};

		SkRRect skRRect;
		SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
		skRRect.setRectRadii(skRect, corners);

		canvas->clipRRect(skRRect, SkClipOp::kIntersect, true);
	}

	Size Rounded::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		return child->getSize(boundaries);
	}

	std::vector<ElementWithRect> Rounded::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Rect childRect = {
			.size = rect.size,
			.position = { .x=0, .y=0 }
		};
		ElementWithRect childElement(child, childRect);
		return { childElement };
	}
}

//
// Created by noartem on 13.04.2022.
//

#include "Background.h"

namespace elementor::elements {
	Size Background::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		return getChild()->getSize(boundaries);
	}

	void Background::paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		SkPaint paint;
		paint.setColor(color);

		SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
		canvas->drawRect(skRect, paint);
	}

	std::vector <ElementWithRect> Background::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Rect childRect = {
			.size = rect.size,
			.position = { .x = 0.0f, .y = 0.0f },
		};

		ElementWithRect childElementWithRect(child, childRect);
		return { childElementWithRect };
	}
}

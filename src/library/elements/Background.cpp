//
// Created by noartem on 13.04.2022.
//

#include "Background.h"

namespace elementor::elements {
	SkColor Background::getColor() const {
		return this->color;
	}

	void Background::setColor(SkColor skColor) {
		this->color = skColor;
	}

	void Background::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		this->color = makeSkColorFromRGBA(r, g, b, a);
	}

	void Background::setColor(uint8_t r, uint8_t g, uint8_t b) {
		this->color = makeSkColorFromRGB(r, g, b);
	}

	void Background::setColor(const std::string_view& hex) {
		if (hex.empty()) {
			return;
		}

		this->color = makeSkColorFromHex(std::string(hex));
	}

	Size Background::getSize(const Boundaries& boundaries) {
		if (this->hasChild()) {
			return this->getChild()->getSize(boundaries);
		}

		return boundaries.max;
	}

	void Background::paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		SkPaint paint;
		paint.setColor(this->color);

		SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
		canvas->drawRect(skRect, paint);
	}

	std::vector<ElementWithRect> Background::getChildren(const ElementRect& rect) {
		std::vector<ElementWithRect> children;

		if (this->hasChild()) {
			ElementWithRect childElement(this->getChild(), { rect.size, 0, 0 });
			children.push_back(childElement);
		}

		return children;
	}
}

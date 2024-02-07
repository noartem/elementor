//
// Created by noartem on 05.08.2022.
//

#include "ParagraphPlaceholder.h"

namespace elementor::elements {

	skia::textlayout::PlaceholderAlignment ParagraphPlaceholder::getSkPlaceholderAlignment() const {
		switch (this->alignment) {
		case ParagraphPlaceholderAlignment::Baseline:
			return skia::textlayout::PlaceholderAlignment::kBaseline;
		case ParagraphPlaceholderAlignment::AboveBaseline:
			return skia::textlayout::PlaceholderAlignment::kAboveBaseline;
		case ParagraphPlaceholderAlignment::BelowBaseline:
			return skia::textlayout::PlaceholderAlignment::kBelowBaseline;
		case ParagraphPlaceholderAlignment::Top:
			return skia::textlayout::PlaceholderAlignment::kTop;
		case ParagraphPlaceholderAlignment::Bottom:
			return skia::textlayout::PlaceholderAlignment::kBottom;
		case ParagraphPlaceholderAlignment::Middle:
			return skia::textlayout::PlaceholderAlignment::kMiddle;
		default:
			return skia::textlayout::PlaceholderAlignment::kBaseline;
		}
	}

	skia::textlayout::TextBaseline ParagraphPlaceholder::getSkBaseline() const {
		switch (this->baseline) {
		case TextBaseline::Alphabetic:
			return skia::textlayout::TextBaseline::kAlphabetic;
		case TextBaseline::Ideographic:
			return skia::textlayout::TextBaseline::kIdeographic;
		default:
			return skia::textlayout::TextBaseline::kAlphabetic;
		}
	}

	skia::textlayout::PlaceholderStyle ParagraphPlaceholder::getSkPlaceholderStyle(const Size& size) const {
		return {
			size.width,
			size.height,
			getSkPlaceholderAlignment(),
			getSkBaseline(),
			offset
		};
	}

	Size ParagraphPlaceholder::getSize(const Boundaries& boundaries) {
		if (doesNotHaveChild()) {
			return boundaries.max;
		}

		return child->getSize(boundaries);
	}

	std::vector <ElementWithRect> ParagraphPlaceholder::getChildren(const ElementRect& rect) {
		if (doesNotHaveChild()) {
			return {};
		}

		Rect childRect = {
			.size = rect.size,
			.position = { .x = 0, .y= 0 },
		};
		ElementWithRect childElement(child, childRect);
		return { childElement };
	}
}
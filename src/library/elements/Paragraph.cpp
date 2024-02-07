//
// Created by noartem on 04.08.2022.
//

#include "Paragraph.h"

#include <include/core/SkFontMgr.h>
#include <include/core/SkFontStyle.h>
#include <modules/skparagraph/include/TypefaceFontProvider.h>

#include "ParagraphPlaceholder.h"

namespace elementor::elements {
	sk_sp<skia::textlayout::FontCollection>
	Paragraph::makeFontCollection(const std::shared_ptr<ApplicationContext>& ctx) const {
		sk_sp<skia::textlayout::FontCollection> fontCollection = sk_make_sp<skia::textlayout::FontCollection>();
		fontCollection->setDefaultFontManager(SkFontMgr::RefDefault());
		fontCollection->setDynamicFontManager(ctx->getSkFontManager());
		return fontCollection;
	}

	skia::textlayout::TextStyle Paragraph::makeDefaultTextStyle() const {
		skia::textlayout::TextStyle textStyle;
		textStyle.setFontSize(16);
		textStyle.setColor(SK_ColorBLACK);
		textStyle.setFontStyle(SkFontStyle{ SkFontStyle::Weight::kNormal_Weight,
											SkFontStyle::Width::kNormal_Width,
											SkFontStyle::Slant::kUpright_Slant });
		return textStyle;
	}

	skia::textlayout::ParagraphStyle Paragraph::makeParagraphStyle() const {
		skia::textlayout::ParagraphStyle paragraphStyle{};
		paragraphStyle.setTextStyle(makeDefaultTextStyle());
		paragraphStyle.setTextDirection(getSkTextDirection());
		return paragraphStyle;
	}

	skia::textlayout::ParagraphBuilderImpl
	Paragraph::makeBuilder(const std::shared_ptr<ApplicationContext>& ctx) const {
		skia::textlayout::ParagraphStyle paragraphStyle = makeParagraphStyle();
		sk_sp<skia::textlayout::FontCollection> fontCollection = makeFontCollection(ctx);
		skia::textlayout::ParagraphBuilderImpl builder{ paragraphStyle, fontCollection };
		return builder;
	}

	skia::textlayout::TextAlign Paragraph::getSkTextAlign() const {
		switch (textAlign) {
		case TextAlign::Left:
			return skia::textlayout::TextAlign::kLeft;
		case TextAlign::Right:
			return skia::textlayout::TextAlign::kRight;
		case TextAlign::Center:
			return skia::textlayout::TextAlign::kCenter;
		case TextAlign::Justify:
			return skia::textlayout::TextAlign::kJustify;
		case TextAlign::Start:
			return skia::textlayout::TextAlign::kStart;
		case TextAlign::End:
			return skia::textlayout::TextAlign::kEnd;
		default:
			return skia::textlayout::TextAlign::kLeft;
		}
	}

	skia::textlayout::TextDirection Paragraph::getSkTextDirection() const {
		switch (textDirection) {
		case TextDirection::LeftToRight:
			return skia::textlayout::TextDirection::kLtr;
		case TextDirection::RightToLeft:
			return skia::textlayout::TextDirection::kRtl;
		default:
			return skia::textlayout::TextDirection::kLtr;
		}
	}

	skia::textlayout::PlaceholderStyle Paragraph::makeElementChildPlaceholderStyle(const Size& childSize) const {
		return {
			childSize.width,
			childSize.height,
			skia::textlayout::PlaceholderAlignment::kMiddle,
			skia::textlayout::TextBaseline::kAlphabetic,
			0.0f,
		};
	}

	skia::textlayout::PlaceholderStyle Paragraph::makeChildPlaceholderStyle(
		const std::shared_ptr<Element>& child
	) const {
		Size childSize = child->getSize(InfiniteBoundaries);

		auto childPlaceholder = std::dynamic_pointer_cast<ParagraphPlaceholder>(child);
		if (childPlaceholder) {
			return childPlaceholder->getSkPlaceholderStyle(childSize);
		}

		return makeElementChildPlaceholderStyle(childSize);
	}

	std::unique_ptr<skia::textlayout::Paragraph> Paragraph::makeSkParagraph() const {
		skia::textlayout::ParagraphBuilderImpl builder = makeBuilder(ctx);

		for (const std::shared_ptr<Element>& child: getChildrenList()) {
			auto textChild = std::dynamic_pointer_cast<Text>(child);
			if (textChild) {
				auto textChildValue = textChild->getText();

				builder.pushStyle(textChild->makeSkTextStyle());
				builder.addText(textChildValue.data(), textChildValue.size());
				builder.pop();
			} else {
				builder.addPlaceholder(makeChildPlaceholderStyle(child));
			}
		}

		std::unique_ptr<skia::textlayout::Paragraph> paragraph = builder.Build();

		paragraph->updateTextAlign(getSkTextAlign());

		return paragraph;
	}

	void Paragraph::updateSkParagraph() {
		auto pixelScale = ctx->getPixelScale();
		if (skParagraph != nullptr && pixelScale == lastPixelScale) {
			return;
		}

		skParagraph = makeSkParagraph();
		lastPixelScale = pixelScale;
	}

	Size Paragraph::getSize(const Boundaries& boundaries) {
		updateSkParagraph();

		skParagraph->layout(boundaries.max.width);
		Size paragraphSize = {
			.width = skParagraph->getMaxWidth(),
			.height = skParagraph->getHeight()
		};

		return fitSizeInBoundaries(paragraphSize, boundaries);
	}

	void Paragraph::paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		updateSkParagraph();

		skParagraph->layout(rect.size.width);
		skParagraph->paint(canvas, 0, 0);
	}

	std::vector<ElementWithRect> Paragraph::getChildren(const ElementRect& rect) {
		updateSkParagraph();

		std::vector<ElementWithRect> childrenElements;

		std::vector<skia::textlayout::TextBox> placeholdersRects = skParagraph->getRectsForPlaceholders();
		for (unsigned int i = 0; i < placeholdersRects.size(); i++) {
			if (placeholdersChildren.size() <= i) {
				break;
			}

			const auto& child = placeholdersChildren[i];

			SkRect childSkRect = placeholdersRects[i].rect;
			Rect childRect = {
				.size = { .width = childSkRect.width(), .height = childSkRect.height() },
				.position = { .x = childSkRect.x(), .y = childSkRect.y() },
			};

			ElementWithRect childElement{ child, childRect };
			childrenElements.push_back(childElement);
		}

		return childrenElements;
	}

	void Paragraph::setChildren(const std::vector<std::shared_ptr<Element>>& newChildren) {
		children = newChildren;
		skParagraph = nullptr;

		placeholdersChildren.clear();
		for (const auto& child: newChildren) {
			auto textChild = std::dynamic_pointer_cast<Text>(child);
			if (textChild) {
				continue;
			}

			placeholdersChildren.push_back(child);
		}
	}

	std::optional<Rect> Paragraph::getGlyphRect(unsigned glyphOffset) {
		updateSkParagraph();

		auto textBoxes = skParagraph->getRectsForRange(
			glyphOffset,
			glyphOffset + 1,
			skia::textlayout::RectHeightStyle::kMax,
			skia::textlayout::RectWidthStyle::kMax
		);

		for (auto textBox : textBoxes) {
			Rect textBoxRect = {
				.size = {
					.width = textBox.rect.width(),
					.height = textBox.rect.height(),
				},
				.position = {
					.x = textBox.rect.left(),
					.y = textBox.rect.top(),
				}
			};

			return textBoxRect;
		}

		return std::nullopt;
	}
}
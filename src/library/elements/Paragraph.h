//
// Created by noartem on 04.08.2022.
//

#ifndef ELEMENTOR_PARAGRAPH_H
#define ELEMENTOR_PARAGRAPH_H

#include "../include.h"

#include <modules/skparagraph/src/ParagraphBuilderImpl.h>

#include "Text.h"

namespace elementor::elements {

	struct ParagraphProps {
		std::optional <TextAlign> textAlign;
		std::optional <TextDirection> textDirection;
		const std::vector <std::shared_ptr<Element>>& children = {};
	};

	class Paragraph : public Element, private WithChildren {
	public:
		Paragraph(const std::shared_ptr <ApplicationContext>& ctx, const ParagraphProps& props)
			: Element(ctx) {
			if (props.textAlign.has_value()) setTextAlign(props.textAlign.value());
			if (props.textDirection.has_value()) setTextDirection(props.textDirection.value());
			setChildren(props.children);
		}

		static std::shared_ptr <Paragraph> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			const ParagraphProps& props
		) {
			return std::make_shared<Paragraph>(ctx, props);
		}

		static std::shared_ptr <Paragraph> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			std::shared_ptr <Paragraph>& elementRef,
			const ParagraphProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr <Paragraph> New(const std::shared_ptr <ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		[[nodiscard]] TextAlign getTextAlign() const {
			return textAlign;
		}

		void setTextAlign(TextAlign newTextAlign) {
			markChanged();
			textAlign = newTextAlign;
		}

		[[nodiscard]] TextDirection getTextDirection() const {
			return textDirection;
		}

		void setTextDirection(TextDirection newTextDirection) {
			markChanged();
			textDirection = newTextDirection;
		}

		std::optional <Rect> getGlyphRect(unsigned glyphOffset);

		Size getSize(const Boundaries& boundaries) override;

		void paintBackground(SkCanvas* canvas, const ElementRect& rect) override;

		std::vector <ElementWithRect> getChildren(const ElementRect& rect) override;

		void setChildren(const std::vector <std::shared_ptr<Element>>& newChildren);

		[[nodiscard]] bool isChanged() const override;

		bool popChanged() override;

	protected:
		void markChanged() override {
			Element::markChanged();
			skParagraph = nullptr;
		}

	private:
		TextAlign textAlign = TextAlign::Left;
		TextDirection textDirection = TextDirection::LeftToRight;

		std::unique_ptr <skia::textlayout::Paragraph> skParagraph;
		std::vector <std::shared_ptr<Element>> placeholdersChildren;

		float lastPixelScale;

		[[nodiscard]] bool isTextChildrenChanged() const;

		bool popTextChildrenChanged();

		sk_sp <skia::textlayout::FontCollection> makeFontCollection(
			const std::shared_ptr <ApplicationContext>& ctx
		) const;

		skia::textlayout::TextStyle makeDefaultTextStyle() const;

		skia::textlayout::ParagraphStyle makeParagraphStyle() const;

		skia::textlayout::ParagraphBuilderImpl makeBuilder(const std::shared_ptr <ApplicationContext>& ctx) const;

		skia::textlayout::TextAlign getSkTextAlign() const;

		skia::textlayout::TextDirection getSkTextDirection() const;

		skia::textlayout::PlaceholderStyle makeElementChildPlaceholderStyle(const Size& childSize) const;

		skia::textlayout::PlaceholderStyle makeChildPlaceholderStyle(const std::shared_ptr <Element>& child) const;

		std::unique_ptr <skia::textlayout::Paragraph> makeSkParagraph() const;

		void updateSkParagraph();
	};

	void paragraph();
}


#endif //ELEMENTOR_PARAGRAPH_H

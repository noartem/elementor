//
// Created by noartem on 04.08.2022.
//

#ifndef ELEMENTOR_PARAGRAPH_PLACEHOLDER_H
#define ELEMENTOR_PARAGRAPH_PLACEHOLDER_H

#include "../include.h"

#include "Text.h"

namespace elementor::elements {
	enum class ParagraphPlaceholderAlignment {
		Baseline,
		AboveBaseline,
		BelowBaseline,
		Top,
		Bottom,
		Middle,
	};

	struct ParagraphPlaceholderProps {
		std::optional<ParagraphPlaceholderAlignment> alignment;
		std::optional<TextBaseline> baseline;
		std::optional<float> offset;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class ParagraphPlaceholder : public Element, public WithChild {
	public:
		ParagraphPlaceholder(const std::shared_ptr<ApplicationContext>& ctx, const ParagraphPlaceholderProps& props)
			: Element(ctx),
			  WithChild(props.child) {
			if (props.alignment.has_value()) setAlignment(props.alignment.value());
			if (props.baseline.has_value()) setBaseline(props.baseline.value());
			if (props.offset.has_value()) setOffset(props.offset.value());
		}

		static std::shared_ptr<ParagraphPlaceholder> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const ParagraphPlaceholderProps& props
		) {
			return std::make_shared<ParagraphPlaceholder>(ctx, props);
		}

		static std::shared_ptr<ParagraphPlaceholder> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		ParagraphPlaceholderAlignment getAlignment() const {
			return alignment;
		}

		void setAlignment(ParagraphPlaceholderAlignment newAlignment) {
			alignment = newAlignment;
		}

		[[nodiscard]] TextBaseline getBaseline() const {
			return baseline;
		}

		void setBaseline(TextBaseline newBaseline) {
			baseline = newBaseline;
		}

		[[nodiscard]] float getOffset() const {
			return offset;
		}

		void setOffset(float newOffset) {
			offset = newOffset;
		}

		skia::textlayout::PlaceholderStyle getSkPlaceholderStyle(const Size& size) const;

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		ParagraphPlaceholderAlignment alignment = ParagraphPlaceholderAlignment::Middle;
		TextBaseline baseline = TextBaseline::Alphabetic;
		float offset = 0;

		skia::textlayout::PlaceholderAlignment getSkPlaceholderAlignment() const;

		skia::textlayout::TextBaseline getSkBaseline() const;
	};
}


#endif //ELEMENTOR_PARAGRAPH_PLACEHOLDER_H

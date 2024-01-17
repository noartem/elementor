//
// Created by noartem on 11.06.2022.
//

#ifndef ELEMENTOR_TEXT_H
#define ELEMENTOR_TEXT_H

#include "../include.h"

#include <include/core/SkFont.h>
#include <include/core/SkFontStyle.h>
#include <modules/skparagraph/include/TextStyle.h>

namespace elementor::elements {
	enum class TextAlign {
		Left,
		Right,
		Center,
		Justify,
		Start,
		End,
	};

	enum class TextDirection {
		LeftToRight,
		RightToLeft,
	};

	enum class TextBaseline {
		Alphabetic,
		Ideographic,
	};

	enum class FontSlant {
		Upright,
		Italic,
		Oblique,
	};

	enum class FontEdging {
		Alias,
		AntiAlias,
		SubpixelAntiAlias,
	};

	enum class TextDecoration {
		NoDecoration,
		Underline,
		Overline,
		LineThrough,
	};

	enum class TextDecorationMode {
		Gaps,
		Through,
	};

	enum class TextDecorationStyle {
		Solid,
		Double,
		Dotted,
		Dashed,
		Wavy,
	};

	struct TextProps {
		std::optional<std::string_view> text;
		std::optional<std::string_view> fontColor;
		std::optional<float> fontSize;
		std::optional<float> fontSkew;
		std::optional<float> fontScale;
		std::optional<float> fontWeight;
		std::optional<float> fontWidth;
		std::optional<FontSlant> fontSlant;
		std::optional<std::string_view> fontFamily;
		std::optional<FontEdging> fontEdging;
		std::optional<TextDecoration> decoration;
		std::optional<TextDecorationMode> decorationMode;
		std::optional<TextDecorationStyle> decorationStyle;
		std::optional<SkColor> decorationColor;
		std::optional<float> decorationThicknessMultiplier;
		std::optional<std::string_view> locale;
	};

	class Text : public Element {
	public:
		explicit Text(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx) {
		}

		Text(const std::shared_ptr<ApplicationContext>& ctx, const TextProps& props)
			: Element(ctx) {
			if (props.text.has_value())
				setText(props.text.value());
			if (props.fontColor.has_value())
				setFontColor(props.fontColor.value());
			if (props.fontSize.has_value())
				setFontSize(props.fontSize.value());
			if (props.fontSkew.has_value())
				setFontSkew(props.fontSkew.value());
			if (props.fontScale.has_value())
				setFontScale(props.fontScale.value());
			if (props.fontWeight.has_value())
				setFontWeight(props.fontWeight.value());
			if (props.fontWidth.has_value())
				setFontWidth(props.fontWidth.value());
			if (props.fontSlant.has_value())
				setFontSlant(props.fontSlant.value());
			if (props.fontFamily.has_value())
				setFontFamily(props.fontFamily.value());
			if (props.fontEdging.has_value())
				setFontEdging(props.fontEdging.value());
			if (props.decoration.has_value())
				setDecoration(props.decoration.value());
			if (props.decorationMode.has_value())
				setDecorationMode(props.decorationMode.value());
			if (props.decorationStyle.has_value())
				setDecorationStyle(props.decorationStyle.value());
			if (props.decorationColor.has_value())
				setDecorationColor(props.decorationColor.value());
			if (props.decorationThicknessMultiplier.has_value())
				setDecorationThicknessMultiplier(props.decorationThicknessMultiplier.value());
			if (props.locale.has_value())
				setLocale(props.locale.value());
		}

		static std::shared_ptr<Text> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const TextProps& props
		) {
			return std::make_shared<Text>(ctx, props);
		}

		static std::shared_ptr<Text> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		[[nodiscard]] std::string_view getText() const {
			return text;
		}

		void setText(const std::string_view& newText) {
			text = newText;
		}

		[[nodiscard]] SkColor getFontColor() const {
			return fontColor;
		}

		void setFontColor(SkColor newFontColor) {
			fontColor = newFontColor;
			paint = std::nullopt;
		}

		void setFontColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			setFontColor(makeSkColorFromRGBA(r, g, b, a));
		}

		void setFontColor(uint8_t r, uint8_t g, uint8_t b) {
			setFontColor(makeSkColorFromRGB(r, g, b));
		}

		void setFontColor(const std::string_view& newFontColor) {
			setFontColor(makeSkColorFromHex(std::string(newFontColor)));
		}

		[[nodiscard]] float getFontSize() const {
			return fontSize;
		}

		void setFontSize(float newFontSize) {
			fontSize = newFontSize;
			font = std::nullopt;
		}

		[[nodiscard]] float getFontSkew() const {
			return fontSkew;
		}

		void setFontSkew(float newFontSkew) {
			fontSkew = newFontSkew;
			font = std::nullopt;
		}

		[[nodiscard]] float getFontScale() const {
			return fontScale;
		}

		void setFontScale(float newFontScale) {
			fontScale = newFontScale;
			font = std::nullopt;
		}

		[[nodiscard]] float getFontWeight() const {
			return fontWeight;
		}

		void setFontWeight(float newFontWeight) {
			fontWeight = newFontWeight;
			font = std::nullopt;
		}

		[[nodiscard]] float getFontWidth() const {
			return fontWidth;
		}

		void setFontWidth(float newFontWidth) {
			fontWidth = newFontWidth;
			font = std::nullopt;
		}

		[[nodiscard]] FontSlant getFontSlant() const {
			return fontSlant;
		}

		void setFontSlant(FontSlant newFontSlant) {
			fontSlant = newFontSlant;
			font = std::nullopt;
		}

		[[nodiscard]] std::string_view getFontFamily() const {
			return fontFamily;
		}

		void setFontFamily(const std::string_view& newFontFamily) {
			fontFamily = newFontFamily;
			font = std::nullopt;
		}

		[[nodiscard]] FontEdging getFontEdging() const {
			return fontEdging;
		}

		void setFontEdging(FontEdging newFontEdging) {
			fontEdging = newFontEdging;
			font = std::nullopt;
		}

		[[nodiscard]] TextDecoration getDecoration() const {
			return decoration;
		}

		void setDecoration(TextDecoration newDecoration) {
			decoration = newDecoration;
		}

		[[nodiscard]] TextDecorationMode getDecorationMode() const {
			return decorationMode;
		}

		void setDecorationMode(TextDecorationMode newDecorationMode) {
			decorationMode = newDecorationMode;
		}

		[[nodiscard]] TextDecorationStyle getDecorationStyle() const {
			return decorationStyle;
		}

		void setDecorationStyle(TextDecorationStyle newDecorationStyle) {
			decorationStyle = newDecorationStyle;
		}

		[[nodiscard]] SkColor getDecorationColor() const {
			return decorationColor;
		}

		void setDecorationColor(SkColor newDecorationColor) {
			decorationColor = newDecorationColor;
		}

		void setDecorationColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			setDecorationColor(makeSkColorFromRGBA(r, g, b, a));
		}

		void setDecorationColor(uint8_t r, uint8_t g, uint8_t b) {
			setDecorationColor(makeSkColorFromRGB(r, g, b));
		}

		void setDecorationColor(const std::string_view& color) {
			setDecorationColor(makeSkColorFromHex(std::string(color)));
		}

		[[nodiscard]] float getDecorationThicknessMultiplier() const {
			return decorationThicknessMultiplier;
		}

		void setDecorationThicknessMultiplier(float newDecorationThicknessMultiplier) {
			decorationThicknessMultiplier = newDecorationThicknessMultiplier;
		}

		[[nodiscard]] std::optional<std::string_view> getLocale() const {
			return locale;
		}

		void setLocale(std::optional<std::string_view> newLocale) {
			locale = newLocale;
		}

		skia::textlayout::TextStyle makeSkTextStyle() const;

		Size getSize(const Boundaries& boundaries) override;

		void paintBackground(SkCanvas* canvas, const ElementRect& rect) override;

	private:
		std::string_view text;
		SkColor fontColor = SK_ColorBLACK;
		float fontSize = 16.0;
		float fontSkew = 0.0;
		float fontScale = 1.0;
		float fontWeight = SkFontStyle::kNormal_Weight;
		float fontWidth = SkFontStyle::kNormal_Width;
		FontSlant fontSlant = FontSlant::Upright;
		std::string_view fontFamily;
		FontEdging fontEdging = FontEdging::AntiAlias;
		TextDecoration decoration = TextDecoration::NoDecoration;
		TextDecorationMode decorationMode = TextDecorationMode::Through;
		TextDecorationStyle decorationStyle = TextDecorationStyle::Solid;
		SkColor decorationColor = SK_ColorTRANSPARENT;
		float decorationThicknessMultiplier = 1;
		std::optional<std::string_view> locale;

		float lastPixelScale;

		std::optional<SkFont> font;
		std::optional<SkPaint> paint;

		SkFontStyle::Slant getSkFontStyleSlant() const;

		SkFont::Edging getSkFontEdging() const;

		SkFontStyle makeSkFontStyle() const;

		sk_sp<SkTypeface> makeSkTypeface() const;

		SkFont makeSkFont() const;

		SkPaint makeSkPaint() const;

		skia::textlayout::TextDecoration getSkTextDecoration() const;

		skia::textlayout::TextDecorationMode getSkTextDecorationMode() const;

		skia::textlayout::TextDecorationStyle getSkTextDecorationStyle() const;
	};
}


#endif //ELEMENTOR_TEXT_H

//
// Created by noartem on 11.06.2022.
//

#include "Text.h"

#include <include/core/SkTypeface.h>

namespace elementor::elements {
	SkFontStyle::Slant Text::getSkFontStyleSlant() const {
		switch (fontSlant) {
		case FontSlant::Italic:
			return SkFontStyle::kItalic_Slant;
		case FontSlant::Oblique:
			return SkFontStyle::kOblique_Slant;
		default:
			return SkFontStyle::kUpright_Slant;
		}
	}

	SkFont::Edging Text::getSkFontEdging() const {
		switch (fontEdging) {
		case FontEdging::Alias:
			return SkFont::Edging::kAlias;
		case FontEdging::AntiAlias:
			return SkFont::Edging::kAntiAlias;
		default:
			return SkFont::Edging::kSubpixelAntiAlias;
		}
	}

	SkFontStyle Text::makeSkFontStyle() const {
		return SkFontStyle(fontWeight, fontWidth, getSkFontStyleSlant());
	}

	sk_sp<SkTypeface> Text::makeSkTypeface() const {
		return SkTypeface::MakeFromName(fontFamily.data(), makeSkFontStyle());
	}

	SkFont Text::makeSkFont() const {
		float pixelScale = ctx->getWindowCtx()->getPixelScale();
		float fontSizeScaled = fontSize * pixelScale;

		SkFont skFont;
		skFont.setTypeface(makeSkTypeface());
		skFont.setSize(fontSizeScaled);
		skFont.setScaleX(fontScale);
		skFont.setSkewX(fontSkew);
		skFont.setEdging(getSkFontEdging());
		return skFont;
	}

	SkPaint Text::makeSkPaint() const {
		SkPaint skPaint;
		skPaint.setColor(getFontColor());
		return skPaint;
	}

	skia::textlayout::TextDecoration Text::getSkTextDecoration() const {
		switch (decoration) {
		case TextDecoration::NoDecoration:
			return skia::textlayout::TextDecoration::kNoDecoration;
		case TextDecoration::Underline:
			return skia::textlayout::TextDecoration::kUnderline;
		case TextDecoration::Overline:
			return skia::textlayout::TextDecoration::kOverline;
		case TextDecoration::LineThrough:
			return skia::textlayout::TextDecoration::kLineThrough;
		default:
			return skia::textlayout::TextDecoration::kNoDecoration;
		}
	}

	skia::textlayout::TextDecorationMode Text::getSkTextDecorationMode() const {
		switch (decorationMode) {
		case TextDecorationMode::Gaps:
			return skia::textlayout::TextDecorationMode::kGaps;
		case TextDecorationMode::Through:
			return skia::textlayout::TextDecorationMode::kThrough;
		default:
			return skia::textlayout::TextDecorationMode::kGaps;
		}
	}

	skia::textlayout::TextDecorationStyle Text::getSkTextDecorationStyle() const {
		switch (decorationStyle) {
		case TextDecorationStyle::Solid:
			return skia::textlayout::TextDecorationStyle::kSolid;
		case TextDecorationStyle::Double:
			return skia::textlayout::TextDecorationStyle::kDouble;
		case TextDecorationStyle::Dotted:
			return skia::textlayout::TextDecorationStyle::kDotted;
		case TextDecorationStyle::Dashed:
			return skia::textlayout::TextDecorationStyle::kDashed;
		case TextDecorationStyle::Wavy:
			return skia::textlayout::TextDecorationStyle::kWavy;
		default:
			return skia::textlayout::TextDecorationStyle::kSolid;
		}
	}

	skia::textlayout::TextStyle Text::makeSkTextStyle() const {
		float pixelScale = ctx->getWindowCtx()->getPixelScale();
		float fontSizeScaled = fontSize * pixelScale;

		auto defaultLocale = ctx->getPlatformCtx()->getLocale();
		auto localeOrDefault = locale.value_or(defaultLocale);

		skia::textlayout::TextStyle textStyle;
		textStyle.setFontSize(fontSizeScaled);
		textStyle.setFontFamilies({ SkString(fontFamily) });
		textStyle.setLocale(SkString(localeOrDefault));
		textStyle.setForegroundColor(makeSkPaint());
		textStyle.setFontStyle(makeSkFontStyle());
		textStyle.setDecoration(getSkTextDecoration());
		textStyle.setDecorationMode(getSkTextDecorationMode());
		textStyle.setDecorationStyle(getSkTextDecorationStyle());
		textStyle.setDecorationColor(getDecorationColor());
		textStyle.setDecorationThicknessMultiplier(getDecorationThicknessMultiplier());
		return textStyle;
	}

	Size Text::getSize(const Boundaries& boundaries) {
		float pixelScale = ctx->getWindowCtx()->getPixelScale();

		if (!font.has_value() || pixelScale != lastPixelScale) font = makeSkFont();
		if (!paint.has_value()) paint = makeSkPaint();
		lastPixelScale = pixelScale;

		SkRect textRect;
		font.value().measureText(text.data(), text.size(), SkTextEncoding::kUTF8, &textRect, &paint.value());

		Size textSize = {
			.width = textRect.width(),
			.height = textRect.height()
		};

		return fitSizeInBoundaries(textSize, boundaries);
	}

	void Text::paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		float pixelScale = ctx->getWindowCtx()->getPixelScale();

		if (!font.has_value() || pixelScale != lastPixelScale) font = makeSkFont();
		if (!paint.has_value()) paint = makeSkPaint();
		lastPixelScale = pixelScale;

		canvas->drawString(text.data(), 0, rect.size.height, font.value(), paint.value());
	}
}

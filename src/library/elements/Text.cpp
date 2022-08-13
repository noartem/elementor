//
// Created by noartem on 11.06.2022.
//

#include "Text.h"
#include "../String.h"
#include "../Color.h"

#include <include/core/SkTypeface.h>

#include <algorithm>

namespace elementor::elements {
    Text *text() {
        return new Text();
    }

    Text *Text::setText(std::u32string text) {
        this->text = toUTF8(text);
        return this;
    }

    Text *Text::setText(std::string text) {
        this->text = text;
        return this;
    }

    std::string Text::getText() {
        return this->text;
    }

    Text *Text::setFontColor(SkColor color) {
        this->fontColor = color;
        this->paint = std::nullopt;
        return this;
    }

    Text *Text::setFontColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->fontColor = makeSkColorFromRGBA(r, g, b, a);
        this->paint = std::nullopt;
        return this;
    }

    Text *Text::setFontColor(uint8_t r, uint8_t g, uint8_t b) {
        this->fontColor = makeSkColorFromRGB(r, g, b);
        this->paint = std::nullopt;
        return this;
    }

    Text *Text::setFontColor(std::string hex) {
        this->fontColor = makeSkColorFromHex(hex);
        this->paint = std::nullopt;
        return this;
    }

    SkColor Text::getFontColor() {
        return this->fontColor;
    }

    Text *Text::setFontSize(float size) {
        this->fontSize = size;
        this->font = std::nullopt;
        return this;
    }

    float Text::getFontSize() {
        return this->fontSize;
    }

    Text *Text::setFontSkew(float skew) {
        this->fontSkew = skew;
        this->font = std::nullopt;
        return this;
    }

    float Text::getFontSkew() {
        return this->fontSkew;
    }

    Text *Text::setFontScale(float scale) {
        this->fontScale = scale;
        this->font = std::nullopt;
        return this;
    }

    float Text::getFontScale() {
        return this->fontScale;
    }

    Text *Text::setFontWeight(float weight) {
        this->fontWeight = weight;
        this->font = std::nullopt;
        return this;
    }

    float Text::getFontWeight() {
        return this->fontWeight;
    }

    Text *Text::setFontWidth(float width) {
        this->fontWidth = width;
        this->font = std::nullopt;
        return this;
    }

    float Text::getFontWidth() {
        return this->fontWidth;
    }

    Text *Text::setFontSlant(FontSlant slant) {
        this->fontSlant = slant;
        this->font = std::nullopt;
        return this;
    }

    FontSlant Text::getFontSlant() {
        return this->fontSlant;
    }

    Text *Text::setFontFamily(std::string fontFamily) {
        this->fontFamily = fontFamily;
        this->font = std::nullopt;
        return this;
    }

    std::string Text::getFontFamily() {
        return this->fontFamily;
    }

    Text *Text::setFontEdging(FontEdging edging) {
        this->fontEdging = edging;
        this->font = std::nullopt;
        return this;
    }

    FontEdging Text::getFontEdging() {
        return this->fontEdging;
    }

    Text *Text::setDecoration(TextDecoration decoration) {
        this->decoration = decoration;
        return this;
    }

    TextDecoration Text::getDecoration() {
        return this->decoration;
    }

    Text *Text::setDecorationMode(TextDecorationMode decorationMode) {
        this->decorationMode = decorationMode;
        return this;
    }

    TextDecorationMode Text::getDecorationMode() {
        return this->decorationMode;
    }

    Text *Text::setDecorationStyle(TextDecorationStyle decorationStyle) {
        this->decorationStyle = decorationStyle;
        return this;
    }

    TextDecorationStyle Text::getDecorationStyle() {
        return this->decorationStyle;
    }

    Text *Text::setDecorationColor(SkColor decorationColor) {
        this->decorationColor = decorationColor;
        return this;
    }

    Text *Text::setDecorationColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->decorationColor = makeSkColorFromRGBA(r, g, b, a);
        this->decoration = decoration;
        return this;
    }

    Text *Text::setDecorationColor(uint8_t r, uint8_t g, uint8_t b) {
        this->decorationColor = makeSkColorFromRGB(r, g, b);
        return this;
    }

    Text *Text::setDecorationColor(std::string hex) {
        this->decorationColor = makeSkColorFromHex(hex);
        return this;
    }

    SkColor Text::getDecorationColor() {
        return this->decorationColor;
    }

    Text *Text::setDecorationThicknessMultiplier(float multiplier) {
        this->decorationThicknessMultiplier = multiplier;
        return this;
    }

    float Text::getDecorationThicknessMultiplier() {
        return this->decorationThicknessMultiplier;
    }

    SkFontStyle::Slant Text::getSkFontStyleSlant() {
        switch (this->fontSlant) {
            case FontSlant::Italic:
                return SkFontStyle::kItalic_Slant;
            case FontSlant::Oblique:
                return SkFontStyle::kOblique_Slant;
            default:
                return SkFontStyle::kUpright_Slant;
        }
    }

    SkFont::Edging Text::getSkFontEdging() {
        switch (this->fontEdging) {
            case FontEdging::Alias:
                return SkFont::Edging::kAlias;
            case FontEdging::AntiAlias:
                return SkFont::Edging::kAntiAlias;
            default:
                return SkFont::Edging::kSubpixelAntiAlias;
        }
    }

    SkFontStyle Text::makeSkFontStyle() {
        return SkFontStyle(this->fontWeight, this->fontWidth, this->getSkFontStyleSlant());
    }

    sk_sp<SkTypeface> Text::makeSkTypeface() {
        return SkTypeface::MakeFromName(this->fontFamily.c_str(), this->makeSkFontStyle());
    }

    SkFont Text::makeSkFont(ApplicationContext *ctx) {
        SkFont font;
        font.setTypeface(this->makeSkTypeface());
        font.setSize(this->fontSize * ctx->window->getMonitorPixelScale());
        font.setScaleX(this->fontScale);
        font.setSkewX(this->fontSkew);
        font.setEdging(this->getSkFontEdging());
        return font;
    }

    SkPaint Text::makeSkPaint() {
        SkPaint paint;
        paint.setColor(this->getFontColor());
        return paint;
    }

    sktextlayout::TextDecoration Text::getSkTextDecoration() {
        switch (this->decoration) {
            case TextDecoration::NoDecoration:
                return sktextlayout::TextDecoration::kNoDecoration;
            case TextDecoration::Underline:
                return sktextlayout::TextDecoration::kUnderline;
            case TextDecoration::Overline:
                return sktextlayout::TextDecoration::kOverline;
            case TextDecoration::LineThrough:
                return sktextlayout::TextDecoration::kLineThrough;
            default:
                return sktextlayout::TextDecoration::kNoDecoration;
        }
    }

    sktextlayout::TextDecorationMode Text::getSkTextDecorationMode() {
        switch (this->decorationMode) {
            case TextDecorationMode::Gaps:
                return sktextlayout::TextDecorationMode::kGaps;
            case TextDecorationMode::Through:
                return sktextlayout::TextDecorationMode::kThrough;
            default:
                return sktextlayout::TextDecorationMode::kGaps;
        }
    }

    sktextlayout::TextDecorationStyle Text::getSkTextDecorationStyle() {
        switch (this->decorationStyle) {
            case TextDecorationStyle::Solid:
                return sktextlayout::TextDecorationStyle::kSolid;
            case TextDecorationStyle::Double:
                return sktextlayout::TextDecorationStyle::kDouble;
            case TextDecorationStyle::Dotted:
                return sktextlayout::TextDecorationStyle::kDotted;
            case TextDecorationStyle::Dashed:
                return sktextlayout::TextDecorationStyle::kDashed;
            case TextDecorationStyle::Wavy:
                return sktextlayout::TextDecorationStyle::kWavy;
            default:
                return sktextlayout::TextDecorationStyle::kSolid;
        }
    }

    sktextlayout::TextStyle Text::makeSkTextStyle(ApplicationContext *ctx) {
        sktextlayout::TextStyle textStyle;
        textStyle.setFontSize(this->fontSize * ctx->window->getMonitorPixelScale());
        textStyle.setFontFamilies({SkString(this->fontFamily)});
        textStyle.setForegroundColor(this->makeSkPaint());
        textStyle.setFontStyle(this->makeSkFontStyle());
        textStyle.setDecoration(this->getSkTextDecoration());
        textStyle.setDecorationMode(this->getSkTextDecorationMode());
        textStyle.setDecorationStyle(this->getSkTextDecorationStyle());
        textStyle.setDecorationColor(this->getDecorationColor());
        textStyle.setDecorationThicknessMultiplier(this->getDecorationThicknessMultiplier());
        return textStyle;
    }

    Size Text::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (!this->font.has_value()) this->font = this->makeSkFont(ctx);
        if (!this->paint.has_value()) this->paint = this->makeSkPaint();

        SkRect textBounds;
        this->font.value().measureText(this->text.c_str(), this->text.size(), SkTextEncoding::kUTF8, &textBounds, &this->paint.value());
        return fitSizeInBoundaries({textBounds.width(), textBounds.height()}, boundaries);
    }

    void Text::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        if (!this->font.has_value()) this->font = this->makeSkFont(ctx);
        if (!this->paint.has_value()) this->paint = this->makeSkPaint();

        canvas->drawString(this->text.c_str(), 0, rect.size.height, this->font.value(), this->paint.value());
	}
}

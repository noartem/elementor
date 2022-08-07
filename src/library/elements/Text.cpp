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
        font.setSize(this->fontSize * ctx->monitorPixelScale);
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

    sktext::TextStyle Text::makeSkTextStyle(ApplicationContext *ctx) {
        sktext::TextStyle textStyle;
        textStyle.setFontSize(this->fontSize * ctx->monitorPixelScale);
        textStyle.setFontFamilies({SkString(this->fontFamily)});
        textStyle.setForegroundColor(this->makeSkPaint());
        textStyle.setFontStyle(this->makeSkFontStyle());
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

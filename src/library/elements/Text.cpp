//
// Created by noartem on 11.06.2022.
//

#include "Text.h"

#include <include/core/SkTypeface.h>

#include <algorithm>

namespace elementor::elements {
    Text *text() {
        return new Text();
    }

    Text *Text::setText(std::string text) {
        this->text = text;
        this->font = std::nullopt;
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

    Text *Text::setFontColor(uint8_t r, uint8_t g, uint8_t b) {
        this->setFontColor(SkColorSetRGB(r, g, b));
        return this;
    }

    Text *Text::setFontColor(std::string hex) {
        if (hex.size() == 7) {
            hex = hex.substr(1);
        }

        if (hex.size() == 6) {
            uint8_t r = std::stoul(hex.substr(0, 2), nullptr, 16);
            uint8_t g = std::stoul(hex.substr(2, 2), nullptr, 16);
            uint8_t b = std::stoul(hex.substr(4, 2), nullptr, 16);
            this->setFontColor(r, g, b);
        }

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

    SkFont Text::makeSkFont() {
        SkFont font;
        font.setTypeface(this->makeSkTypeface());
        font.setSize(this->fontSize * this->ctx->monitorPixelScale);
        font.setScaleX(this->fontScale);
        font.setSkewX(this->fontSkew);
        font.setEdging(this->getSkFontEdging());
        return font;
    }

    void Text::updateSkFont() {
        if (!this->font) {
            this->font = this->makeSkFont();
        }
    }

    SkPaint Text::makeSkPaint() {
        SkPaint paint;
        paint.setColor(this->getFontColor());
        return paint;
    }

    void Text::updateSkPaint() {
        if (!this->paint) {
            this->paint = this->makeSkPaint();
        }
    }

    Size Text::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        this->ctx = ctx;
        this->updateSkFont();
        this->updateSkPaint();

        SkRect textBounds;
        this->font.value().measureText(this->text.c_str(), this->text.size(), SkTextEncoding::kUTF8, &textBounds, &this->paint.value());

        float width = std::min(std::max(textBounds.width(), boundaries.min.width), boundaries.max.width);
        float height = std::min(std::max(textBounds.height(), boundaries.min.height), boundaries.max.height);
        return fitSizeInBoundaries({width, height}, boundaries);
    }

    void Text::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        this->ctx = ctx;
        this->updateSkFont();
        this->updateSkPaint();

        canvas->drawString(this->text.c_str(), 0, rect.size.height, this->font.value(), this->paint.value());
	}
}

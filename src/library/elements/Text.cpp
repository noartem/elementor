//
// Created by noartem on 11.06.2022.
//

#include "Text.h"
#include "../String.h"
#include "../Color.h"

#include <include/core/SkTypeface.h>

#include <algorithm>
#include <utility>

namespace elementor::elements {
    std::shared_ptr<Text> text() {
        return std::make_shared<Text>();
    }

    std::shared_ptr<Text> Text::setText(std::u32string newText) {
        this->text = toUTF8(newText);
        return shared_from_this();
    }

    std::shared_ptr<Text> Text::setText(std::string newText) {
        this->text = std::move(newText);
        return shared_from_this();
    }

    std::string Text::getText() {
        return this->text;
    }

    std::shared_ptr<Text> Text::setFontColor(SkColor color) {
        this->fontColor = color;
        this->paint = std::nullopt;
        return shared_from_this();
    }

    std::shared_ptr<Text> Text::setFontColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->fontColor = makeSkColorFromRGBA(r, g, b, a);
        this->paint = std::nullopt;
        return shared_from_this();
    }

    std::shared_ptr<Text> Text::setFontColor(uint8_t r, uint8_t g, uint8_t b) {
        this->fontColor = makeSkColorFromRGB(r, g, b);
        this->paint = std::nullopt;
        return shared_from_this();
    }

    std::shared_ptr<Text> Text::setFontColor(std::string hex) {
        this->fontColor = makeSkColorFromHex(std::move(hex));
        this->paint = std::nullopt;
        return shared_from_this();
    }

    SkColor Text::getFontColor() const {
        return this->fontColor;
    }

    std::shared_ptr<Text> Text::setFontSize(float size) {
        this->fontSize = size;
        this->font = std::nullopt;
        return shared_from_this();
    }

    float Text::getFontSize() const {
        return this->fontSize;
    }

    std::shared_ptr<Text> Text::setFontSkew(float skew) {
        this->fontSkew = skew;
        this->font = std::nullopt;
        return shared_from_this();
    }

    float Text::getFontSkew() const {
        return this->fontSkew;
    }

    std::shared_ptr<Text> Text::setFontScale(float scale) {
        this->fontScale = scale;
        this->font = std::nullopt;
        return shared_from_this();
    }

    float Text::getFontScale() const {
        return this->fontScale;
    }

    std::shared_ptr<Text> Text::setFontWeight(float weight) {
        this->fontWeight = weight;
        this->font = std::nullopt;
        return shared_from_this();
    }

    float Text::getFontWeight() const {
        return this->fontWeight;
    }

    std::shared_ptr<Text> Text::setFontWidth(float width) {
        this->fontWidth = width;
        this->font = std::nullopt;
        return shared_from_this();
    }

    float Text::getFontWidth() const {
        return this->fontWidth;
    }

    std::shared_ptr<Text> Text::setFontSlant(FontSlant slant) {
        this->fontSlant = slant;
        this->font = std::nullopt;
        return shared_from_this();
    }

    FontSlant Text::getFontSlant() {
        return this->fontSlant;
    }

    std::shared_ptr<Text> Text::setFontFamily(std::string fontFamily) {
        this->fontFamily = fontFamily;
        this->font = std::nullopt;
        return shared_from_this();
    }

    std::string Text::getFontFamily() {
        return this->fontFamily;
    }

    std::shared_ptr<Text> Text::setFontEdging(FontEdging edging) {
        this->fontEdging = edging;
        this->font = std::nullopt;
        return shared_from_this();
    }

    FontEdging Text::getFontEdging() {
        return this->fontEdging;
    }

    std::shared_ptr<Text> Text::setDecoration(TextDecoration decoration) {
        this->decoration = decoration;
        return shared_from_this();
    }

    TextDecoration Text::getDecoration() {
        return this->decoration;
    }

    std::shared_ptr<Text> Text::setDecorationMode(TextDecorationMode decorationMode) {
        this->decorationMode = decorationMode;
        return shared_from_this();
    }

    TextDecorationMode Text::getDecorationMode() {
        return this->decorationMode;
    }

    std::shared_ptr<Text> Text::setDecorationStyle(TextDecorationStyle decorationStyle) {
        this->decorationStyle = decorationStyle;
        return shared_from_this();
    }

    TextDecorationStyle Text::getDecorationStyle() {
        return this->decorationStyle;
    }

    std::shared_ptr<Text> Text::setDecorationColor(SkColor decorationColor) {
        this->decorationColor = decorationColor;
        return shared_from_this();
    }

    std::shared_ptr<Text> Text::setDecorationColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->decorationColor = makeSkColorFromRGBA(r, g, b, a);
        return shared_from_this();
    }

    std::shared_ptr<Text> Text::setDecorationColor(uint8_t r, uint8_t g, uint8_t b) {
        this->decorationColor = makeSkColorFromRGB(r, g, b);
        return shared_from_this();
    }

    std::shared_ptr<Text> Text::setDecorationColor(std::string hex) {
        this->decorationColor = makeSkColorFromHex(hex);
        return shared_from_this();
    }

    SkColor Text::getDecorationColor() {
        return this->decorationColor;
    }

    std::shared_ptr<Text> Text::setDecorationThicknessMultiplier(float multiplier) {
        this->decorationThicknessMultiplier = multiplier;
        return shared_from_this();
    }

    float Text::getDecorationThicknessMultiplier() {
        return this->decorationThicknessMultiplier;
    }

    std::shared_ptr<Text> Text::setLocale(std::optional<std::string> locale) {
        this->locale = locale;
        return shared_from_this();
    }

    std::optional<std::string> Text::getLocale() {
        return this->locale;
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

    SkFont Text::makeSkFont(std::shared_ptr<ApplicationContext> ctx) {
        SkFont font;
        font.setTypeface(this->makeSkTypeface());
        font.setSize(this->fontSize * ctx->getPixelScale());
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

    sktextlayout::TextStyle Text::makeSkTextStyle(std::shared_ptr<ApplicationContext> ctx) {
        sktextlayout::TextStyle textStyle;
        textStyle.setFontSize(this->fontSize * ctx->getPixelScale());
        textStyle.setFontFamilies({SkString(this->fontFamily)});
        textStyle.setLocale(SkString(this->locale.value_or(ctx->getLocale())));
        textStyle.setForegroundColor(this->makeSkPaint());
        textStyle.setFontStyle(this->makeSkFontStyle());
        textStyle.setDecoration(this->getSkTextDecoration());
        textStyle.setDecorationMode(this->getSkTextDecorationMode());
        textStyle.setDecorationStyle(this->getSkTextDecorationStyle());
        textStyle.setDecorationColor(this->getDecorationColor());
        textStyle.setDecorationThicknessMultiplier(this->getDecorationThicknessMultiplier());
        return textStyle;
    }

    Size Text::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        if (!this->font.has_value() || ctx->getPixelScale() != this->lastPixelScale) this->font = this->makeSkFont(ctx);
        if (!this->paint.has_value()) this->paint = this->makeSkPaint();
        this->lastPixelScale = ctx->getPixelScale();

        SkRect textBounds;
        this->font.value().measureText(this->text.c_str(), this->text.size(), SkTextEncoding::kUTF8, &textBounds, &this->paint.value());
        return fitSizeInBoundaries({textBounds.width(), textBounds.height()}, boundaries);
    }

    void Text::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) {
        if (!this->font.has_value() || ctx->getPixelScale() != this->lastPixelScale) this->font = this->makeSkFont(ctx);
        if (!this->paint.has_value()) this->paint = this->makeSkPaint();
        this->lastPixelScale = ctx->getPixelScale();

        canvas->drawString(this->text.c_str(), 0, rect.size.height, this->font.value(), this->paint.value());
	}
}

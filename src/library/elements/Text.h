//
// Created by noartem on 11.06.2022.
//

#ifndef ELEMENTOR_TEXT_H
#define ELEMENTOR_TEXT_H

#include "../Element.h"

#include <include/core/SkFont.h>
#include <include/core/SkFontStyle.h>
#include <modules/skparagraph/include/TextStyle.h>

namespace sktextlayout = skia::textlayout;

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
        LTR,
        RTL,
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

    class Text : public Element, public std::enable_shared_from_this<Text> {
    public:
        std::shared_ptr<Text> setText(std::u32string newText);

        std::shared_ptr<Text> setText(std::string newText);

        std::string getText();

        std::shared_ptr<Text> setFontColor(SkColor color);

        std::shared_ptr<Text> setFontColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        std::shared_ptr<Text> setFontColor(uint8_t r, uint8_t g, uint8_t b);

        std::shared_ptr<Text> setFontColor(std::string color);

        SkColor getFontColor() const;

        std::shared_ptr<Text> setFontSize(float size);

        float getFontSize() const;

        std::shared_ptr<Text> setFontSkew(float skew);

        float getFontSkew() const;

        std::shared_ptr<Text> setFontScale(float scale);

        float getFontScale() const;

        std::shared_ptr<Text> setFontWeight(float weight);

        float getFontWeight() const;

        std::shared_ptr<Text> setFontWidth(float width);

        float getFontWidth() const;

        std::shared_ptr<Text> setFontSlant(FontSlant slant);

        FontSlant getFontSlant();

        std::shared_ptr<Text> setFontFamily(std::string fontFamily);

        std::string getFontFamily();

        std::shared_ptr<Text> setFontEdging(FontEdging edging);

        FontEdging getFontEdging();

        std::shared_ptr<Text> setDecoration(TextDecoration decoration);

        TextDecoration getDecoration();

        std::shared_ptr<Text> setDecorationMode(TextDecorationMode decorationMode);

        TextDecorationMode getDecorationMode();

        std::shared_ptr<Text> setDecorationStyle(TextDecorationStyle decorationStyle);

        TextDecorationStyle getDecorationStyle();

        std::shared_ptr<Text> setDecorationColor(SkColor color);

        std::shared_ptr<Text> setDecorationColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        std::shared_ptr<Text> setDecorationColor(uint8_t r, uint8_t g, uint8_t b);

        std::shared_ptr<Text> setDecorationColor(std::string color);

        SkColor getDecorationColor();

        std::shared_ptr<Text> setDecorationThicknessMultiplier(float multiplier);

        float getDecorationThicknessMultiplier();

        std::shared_ptr<Text> setLocale(std::optional<std::string> locale);

        std::optional<std::string> getLocale();

        sktextlayout::TextStyle makeSkTextStyle(std::shared_ptr<ApplicationContext> ctx);

        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                     Boundaries boundaries) override;

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas,
                             ElementRect rect) override;

    private:
        std::string text;
        SkColor fontColor = SK_ColorBLACK;
        float fontSize = 16.0;
        float fontSkew = 0.0;
        float fontScale = 1.0;
        float fontWeight = SkFontStyle::kNormal_Weight;
        float fontWidth = SkFontStyle::kNormal_Width;
        FontSlant fontSlant = FontSlant::Upright;
        std::string fontFamily;
        FontEdging fontEdging = FontEdging::AntiAlias;
        TextDecoration decoration = TextDecoration::NoDecoration;
        TextDecorationMode decorationMode = TextDecorationMode::Through;
        TextDecorationStyle decorationStyle = TextDecorationStyle::Solid;
        SkColor decorationColor = SK_ColorTRANSPARENT;
        float decorationThicknessMultiplier = 1;
        std::optional<std::string> locale;

        float lastPixelScale;

        std::optional<SkFont> font;
        std::optional<SkPaint> paint;

        SkFontStyle::Slant getSkFontStyleSlant();

        SkFont::Edging getSkFontEdging();

        SkFontStyle makeSkFontStyle();

        sk_sp<SkTypeface> makeSkTypeface();

        SkFont makeSkFont(std::shared_ptr<ApplicationContext> ctx);

        SkPaint makeSkPaint();

        sktextlayout::TextDecoration getSkTextDecoration();

        sktextlayout::TextDecorationMode getSkTextDecorationMode();

        sktextlayout::TextDecorationStyle getSkTextDecorationStyle();
    };

    std::shared_ptr<Text> text();
}


#endif //ELEMENTOR_TEXT_H

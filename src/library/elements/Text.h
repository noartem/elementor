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

    class Text : public Element {
    public:
        Text *setText(std::u32string text);

        Text *setText(std::string text);

        std::string getText();

        Text *setFontColor(SkColor color);

        Text *setFontColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        Text *setFontColor(uint8_t r, uint8_t g, uint8_t b);

        Text *setFontColor(std::string color);

        SkColor getFontColor();

        Text *setFontSize(float size);

        float getFontSize();

        Text *setFontSkew(float skew);

        float getFontSkew();

        Text *setFontScale(float scale);

        float getFontScale();

        Text *setFontWeight(float weight);

        float getFontWeight();

        Text *setFontWidth(float width);

        float getFontWidth();

        Text *setFontSlant(FontSlant slant);

        FontSlant getFontSlant();

        Text *setFontFamily(std::string fontFamily);

        std::string getFontFamily();

        Text *setFontEdging(FontEdging edging);

        FontEdging getFontEdging();

        Text *setDecoration(TextDecoration decoration);

        TextDecoration getDecoration();

        Text *setDecorationMode(TextDecorationMode decorationMode);

        TextDecorationMode getDecorationMode();

        Text *setDecorationStyle(TextDecorationStyle decorationStyle);

        TextDecorationStyle getDecorationStyle();

        Text *setDecorationColor(SkColor color);

        Text *setDecorationColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        Text *setDecorationColor(uint8_t r, uint8_t g, uint8_t b);

        Text *setDecorationColor(std::string color);

        SkColor getDecorationColor();

        Text *setDecorationThicknessMultiplier(float multiplier);

        float getDecorationThicknessMultiplier();

        sktextlayout::TextStyle makeSkTextStyle(Window *window);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;    

        void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) override;

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

        std::optional<SkFont> font;
        std::optional<SkPaint> paint;

        SkFontStyle::Slant getSkFontStyleSlant();

        SkFont::Edging getSkFontEdging();

        SkFontStyle makeSkFontStyle();

        sk_sp<SkTypeface> makeSkTypeface();

        SkFont makeSkFont(Window *window);

        SkPaint makeSkPaint();

        sktextlayout::TextDecoration getSkTextDecoration();

        sktextlayout::TextDecorationMode getSkTextDecorationMode();

        sktextlayout::TextDecorationStyle getSkTextDecorationStyle();
    };

    Text *text();
}


#endif //ELEMENTOR_TEXT_H

//
// Created by noartem on 11.06.2022.
//

#ifndef ELEMENTOR_TEXT_H
#define ELEMENTOR_TEXT_H

#include "../Element.h"

#include <include/core/SkFont.h>
#include <include/core/SkFontStyle.h>

#include <optional>

namespace elementor::elements {
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

    class Text : public Element {
    public:
        Text *setText(std::string text);

        std::string getText();

        Text *setFontColor(SkColor color);

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

        Text *setFontFile(std::string fontFile);

        std::string getFontFile();

        Text *setFontEdging(FontEdging edging);

        FontEdging getFontEdging();

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;    

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) override;

    private:
        ApplicationContext *ctx;
        std::string text;
        SkColor fontColor = SK_ColorBLACK;
        float fontSize = 16.0;
        float fontSkew = 0.0;
        float fontScale = 1.0;
        float fontWeight = SkFontStyle::kNormal_Weight;
        float fontWidth = SkFontStyle::kNormal_Width;
        FontSlant fontSlant = FontSlant::Upright;
        std::string fontFamily;
        std::string fontFile;
        FontEdging fontEdging = FontEdging::AntiAlias;

        std::optional<SkFont> font;
        std::optional<SkPaint> paint;

        SkFontStyle::Slant getSkFontStyleSlant();

        SkFont::Edging getSkFontEdging();

        SkFontStyle makeSkFontStyle();

        sk_sp<SkTypeface> makeSkTypeface();

        SkFont makeSkFont();

        SkPaint makeSkPaint();

        void updateSkFont();

        void updateSkPaint();
    };

    Text *text();
}


#endif //ELEMENTOR_TEXT_H

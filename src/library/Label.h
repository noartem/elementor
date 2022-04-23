//
// Created by noartem on 22.04.2022.
//

#ifndef ELEMENTOR_LABEL_H
#define ELEMENTOR_LABEL_H

#include "Element.h"

#include <include/core/SkFont.h>

namespace elementor {
    class Label : public Element {
    public:
        Label() {};

        Label(std::string text);

        Label(std::string text, SkColor fontColor);

        Label(std::string text, std::string fontColor);

        Label(std::string text, float fontSize);

        Label(std::string text, SkColor fontColor, float fontSize);

        Label(std::string text, std::string fontColor, float fontSize);

        void setText(std::string text);

        std::string setText();

        void setFontColor(SkColor color);

        void setFontColor(uint8_t r, uint8_t g, uint8_t b);

        void setFontColor(std::string color);

        SkColor getFontColor();

        void setFontSize(float size);

        float getFontSize();

        std::shared_ptr <ElementRenderer> render() override;

    private:
        std::string text;
        SkColor fontColor = SK_ColorBLACK;
        float fontSize = 16.0;
    };

    class LabelRenderer : public ElementRenderer {
    public:
        LabelRenderer(ApplicationContext *context, std::string text, SkColor fontColor, float fontSize);

        RenderSize getSize(RenderBoundaries boundaries) override;    

        void paintBackground(SkCanvas *canvas, RenderSize size) override;

    private:
        std::string text;
        SkColor fontColor;
        float fontSize;
        SkFont font;
        SkRect bounds;
    };
}


#endif //ELEMENTOR_LABEL_H

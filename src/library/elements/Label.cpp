//
// Created by noartem on 22.04.2022.
//

#include "Label.h"

#include <algorithm>

namespace elementor::elements {
    Label *label() {
        return new Label();
    }

    Label *Label::setText(std::string text) {
        this->text = text;
        return this;
    }

    std::string Label::setText() {
        return this->text;
    }

    Label *Label::setFontColor(SkColor color) {
        this->fontColor = color;
        return this;
    }

    Label *Label::setFontColor(uint8_t r, uint8_t g, uint8_t b) {
        this->setFontColor(SkColorSetRGB(r, g, b));
        return this;
    }

    Label *Label::setFontColor(std::string hex) {
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

    SkColor Label::getFontColor() {
        return this->fontColor;
    }

    Label *Label::setFontSize(float size) {
        this->fontSize = size;
        return this;
    }

    float Label::getFontSize() {
        return this->fontSize;
    }

    Size Label::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        SkFont font;
        font.setSize(this->fontSize * ctx->monitorPixelScale);

        SkRect textBounds;
        font.measureText(this->text.c_str(), this->text.size(), SkTextEncoding::kUTF8, &textBounds);

        int width = std::min(std::max((int) ceil(textBounds.width()), boundaries.min.width), boundaries.max.width);
        int height = std::min(std::max((int) ceil(textBounds.height()), boundaries.min.height), boundaries.max.height);
        return fitSizeInBoundaries({width, height}, boundaries);
    }

    void Label::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        SkFont font;
        font.setSize(this->fontSize * ctx->monitorPixelScale);

        SkPaint paint;
        paint.setColor(this->getFontColor());

        canvas->translate(0, rect.size.height);
        canvas->drawString(this->text.c_str(), 0, 0, font, paint);
    }
}

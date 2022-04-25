//
// Created by noartem on 22.04.2022.
//

#include "Label.h"

#include <algorithm>

namespace elementor {
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

    std::shared_ptr <ElementRenderer> Label::render() {
        return std::make_shared<LabelRenderer>(this->context, this->text, this->fontColor, this->fontSize);
    }

    LabelRenderer::LabelRenderer(ApplicationContext *context, std::string text, SkColor fontColor, float fontSize) {
        this->context = context;
        this->text = text;
        this->fontColor = fontColor;
        this->fontSize = fontSize * this->context->monitorPixelScale;
        this->font.setSize(fontSize);
        this->font.measureText(this->text.c_str(), this->text.size(), SkTextEncoding::kUTF8, &this->bounds);
    }

    RenderSize LabelRenderer::getSize(RenderBoundaries boundaries) {
        int textWidth = ceil(this->bounds.width());
        int textHeight = ceil(this->bounds.height());
        int width = std::min(std::max(textWidth, boundaries.min.width), boundaries.max.width);
        int height = std::min(std::max(textHeight, boundaries.min.height), boundaries.max.height);
        return {width, height};
    }

    void LabelRenderer::paintBackground(SkCanvas *canvas, RenderSize size) {
        SkPaint paint;
        paint.setColor(this->fontColor);

        canvas->translate(0, this->bounds.height());
        canvas->drawString(this->text.c_str(), 0, 0, this->font, paint);
    }
}

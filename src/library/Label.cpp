//
// Created by noartem on 22.04.2022.
//

#include "Label.h"

namespace elementor {
    std::shared_ptr <ElementRenderer> Label::render() {
        auto renderer = std::make_shared<LabelRenderer>();
        renderer->text = this->text;
        renderer->fontSize = this->fontSize;
        renderer->fontColor = this->fontColor;
        renderer->context = this->context;
        return renderer;
    }

    SkFont LabelRenderer::makeFont() {
        SkFont font;
        font.setSize(this->fontSize * this->context->monitorPixelScale);
        return font;
    }

    SkRect LabelRenderer::makeTextBounds() {
        SkRect bounds;
        this->makeFont().measureText(this->text.c_str(), this->text.size(), SkTextEncoding::kUTF8, &bounds);
        return bounds;
    }

    RenderSize LabelRenderer::getSize(RenderBoundaries boundaries) {
        SkRect bounds = this->makeTextBounds();
        return {(int) ceil(bounds.width()), (int) ceil(bounds.height())};
    }

    void LabelRenderer::paintBackground(SkCanvas *canvas, RenderSize size) {
        SkFont font = this->makeFont();

        SkPaint paint;
        paint.setColor(this->fontColor);

        SkRect bounds = this->makeTextBounds();
        canvas->translate(0, bounds.height());
        canvas->drawString(this->text.c_str(), 0, 0, font, paint);
    }
}

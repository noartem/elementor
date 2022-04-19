//
// Created by noartem on 13.04.2022.
//

#include "Background.h"

namespace elementor {
    void Background::setColor(uint8_t r, uint8_t g, uint8_t b) {
        this->setColor(r, g, b, 255);
    }

    void Background::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->color = SkColorSetARGB(a, r, g, b);
    }

    void Background::setColor(std::string hex) {
        if (hex.size() == 7) {
            hex = hex.substr(1);
        }

        if (hex.size() != 6) {
            return;
        }

        uint8_t r = std::stoul(hex.substr(0, 2), nullptr, 16);
        uint8_t g = std::stoul(hex.substr(2, 2), nullptr, 16);
        uint8_t b = std::stoul(hex.substr(4, 2), nullptr, 16);
        this->setColor(r, g, b);
    }

    std::shared_ptr <ElementRenderer> Background::render() {
        auto renderer = std::make_shared<BackgroundRenderer>();
        renderer->color = this->color;
        renderer->child = this->child;
        return renderer;
    }

    void BackgroundRenderer::paintBackground(SkCanvas *canvas, RenderPosition start, RenderSize size) {
        SkPaint paint;
        paint.setColor(this->color);

        SkRect rect = SkRect::MakeXYWH(start.x, start.y, size.width, size.height);
        canvas->drawRect(rect, paint);
    }

    std::vector <RenderElement> BackgroundRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement child;
            child.element = this->child;
            child.renderer = this->child->render();
            child.position = {0, 0};
            child.size = size;

            children.push_back(child);
        }

        return children;
    }
}

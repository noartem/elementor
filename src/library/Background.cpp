//
// Created by noartem on 13.04.2022.
//

#include "Background.h"

namespace elementor {
    Background *background() {
        return new Background();
    }

    Background *Background::setColor(SkColor color) {
        this->color = color;
        return this;
    }

    Background *Background::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->setColor(SkColorSetARGB(a, r, g, b));
        return this;
    }

    Background *Background::setColor(uint8_t r, uint8_t g, uint8_t b) {
        this->setColor(r, g, b, 255);
        return this;
    }

    Background *Background::setColor(std::string hex) {
        if (hex.size() == 7) {
            hex = hex.substr(1);
        }

        if (hex.size() == 6) {
            uint8_t r = std::stoul(hex.substr(0, 2), nullptr, 16);
            uint8_t g = std::stoul(hex.substr(2, 2), nullptr, 16);
            uint8_t b = std::stoul(hex.substr(4, 2), nullptr, 16);
            this->setColor(r, g, b);
        }

        return this;
    }

    SkColor Background::getColor() {
        return this->color;
    }

    Background *Background::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    std::shared_ptr <ElementRenderer> Background::render() {
        return std::make_shared<BackgroundRenderer>(this->context, this->color, this->getChild());
    }

    BackgroundRenderer::BackgroundRenderer(ApplicationContext *context, SkColor color, Element *child) {
        this->context = context;
        this->color = color;
        this->child = child;
    }

    void BackgroundRenderer::paintBackground(SkCanvas *canvas, RenderSize size) {
        SkPaint paint;
        paint.setColor(this->color);

        SkRect rect = SkRect::MakeXYWH(0, 0, size.width, size.height);
        canvas->drawRect(rect, paint);
    }

    std::vector <RenderElement> BackgroundRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement child;
            child.element = this->child;
            child.element->context = context;
            child.renderer = this->child->render();
            child.position = {0, 0};
            child.size = size;

            children.push_back(child);
        }

        return children;
    }
}

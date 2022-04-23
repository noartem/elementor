//
// Created by noartem on 13.04.2022.
//

#include "Background.h"

namespace elementor {
    Background::Background(Element *child) {
        this->setChild(child);
    }

    Background::Background(SkColor color) {
        this->setColor(color);
    }

    Background::Background(std::string color) {
        this->setColor(color);
    }

    Background::Background(SkColor color, Element *child) {
        this->setColor(color);
        this->setChild(child);
    }

    Background::Background(std::string color, Element *child) {
        this->setColor(color);
        this->setChild(child);
    }
    
    void Background::setColor(SkColor color) {
        this->color = color;
    }

    void Background::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->setColor(SkColorSetARGB(a, r, g, b));
    }

    void Background::setColor(uint8_t r, uint8_t g, uint8_t b) {
        this->setColor(r, g, b, 255);
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

    SkColor Background::getColor() {
        return this->color;
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

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

    Size Background::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Background::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        SkPaint paint;
        paint.setColor(this->color);

        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        canvas->drawRect(skRect, paint);
    }

    std::vector <RenderElement> Background::getRenderChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.position = {0, 0};
            child.size = size;

            children.push_back(child);
        }

        return children;
    }
}

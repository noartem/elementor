//
// Created by noartem on 13.04.2022.
//

#include "Background.h"
#include "../Color.h"

namespace elementor::elements {
    Background *background() {
        return new Background();
    }

    Background *Background::setColor(SkColor color) {
        this->color = color;
        return this;
    }

    Background *Background::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->color = makeSkColorFromRGBA(r, g, b, a);
        return this;
    }

    Background *Background::setColor(uint8_t r, uint8_t g, uint8_t b) {
        this->color = makeSkColorFromRGB(r, g, b);
        return this;
    }

    Background *Background::setColor(std::string hex) {
        this->color = makeSkColorFromHex(hex);
        return this;
    }

    SkColor Background::getColor() {
        return this->color;
    }

    Background *Background::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Background::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Background::paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) {
        SkPaint paint;
        paint.setColor(this->color);

        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        canvas->drawRect(skRect, paint);
    }

    std::vector <RenderElement> Background::getChildren(ApplicationContext *ctx, Window *window, Size size) {
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

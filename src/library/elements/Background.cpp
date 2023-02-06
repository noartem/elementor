//
// Created by noartem on 13.04.2022.
//

#include "Background.h"

#include <utility>
#include "../Color.h"

namespace elementor::elements {
    std::shared_ptr<Background> background() {
        return std::make_shared<Background>();
    }

    std::shared_ptr<Background> Background::setColor(SkColor skColor) {
        this->color = skColor;
        return shared_from_this();
    }

    std::shared_ptr<Background> Background::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->color = makeSkColorFromRGBA(r, g, b, a);
        return shared_from_this();
    }

    std::shared_ptr<Background> Background::setColor(uint8_t r, uint8_t g, uint8_t b) {
        this->color = makeSkColorFromRGB(r, g, b);
        return shared_from_this();
    }

    std::shared_ptr<Background> Background::setColor(std::string hex) {
        this->color = makeSkColorFromHex(std::move(hex));
        return shared_from_this();
    }

    SkColor Background::getColor() const {
        return this->color;
    }

    std::shared_ptr<Background> Background::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size Background::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                             Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.max;
        }
    }

    void Background::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window,
                                     SkCanvas *canvas, ElementRect rect) {
        SkPaint paint;
        paint.setColor(this->color);

        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        canvas->drawRect(skRect, paint);
    }

    std::vector<RenderElement>
    Background::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector<RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }
}

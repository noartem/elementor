//
// Created by noartem on 13.04.2022.
//

#include "Border.h"

#include <include/core/SkRRect.h>
#include <include/effects/SkDashPathEffect.h>
#include <include/effects/Sk1DPathEffect.h>

namespace elementor::elements {
    Border *border() {
        return new Border();
    }

    Border *Border::setColor(SkColor color) {
        this->color = color;
        return this;
    }

    Border *Border::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->setColor(SkColorSetARGB(a, r, g, b));
        return this;
    }

    Border *Border::setColor(uint8_t r, uint8_t g, uint8_t b) {
        this->setColor(r, g, b, 255);
        return this;
    }

    Border *Border::setColor(std::string hex) {
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

    SkColor Border::getColor() {
        return this->color;
    }

    Border *Border::setWidth(float width) {
        this->width = width;
        return this;
    }

    float Border::getWidth() {
        return this->width;
    }

    Border *Border::setRadius(float radiusX, float radiusY) {
        this->radiusX = radiusX;
        this->radiusY = radiusY;
        return this;
    }

    Border *Border::setRadius(float radiusXY) {
        this->setRadius(radiusXY, radiusXY);
        return this;
    }

    float Border::getRadiusX() {
        return this->radiusX;
    }

    float Border::getRadiusY() {
        return this->radiusY;
    }

    Border *Border::setStyle(BorderStyle style) {
        this->style = style;
        return this;
    }

    BorderStyle Border::getStyle() {
        return this->style;
    }

    Border *Border::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Border::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        if (this->hasChild()) {
            float borderWidth = this->getWidth() * ctx->getPixelScale();
            Boundaries childBoundaries = {{boundaries.min.width - borderWidth * 2, boundaries.min.height - borderWidth * 2}, {boundaries.max.width - borderWidth * 2, boundaries.max.height - borderWidth * 2}};
            Size childSize = this->getChild()->getSize(ctx, window, childBoundaries);
            return {childSize.width + borderWidth * 2, childSize.height + borderWidth * 2};
        } else {
            return boundaries.max;
        }
    }

    void Border::paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) {
        SkPaint paint;
        paint.setColor(this->getColor());
        paint.setStrokeWidth(this->getWidth());
        paint.setStyle(SkPaint::kStroke_Style);
        paint.setAntiAlias(true);

        if (this->style == BorderStyle::Dotted) {
            SkPath path;
            path.addOval(SkRect::MakeWH(this->getWidth() / 2, this->getWidth() / 2));

            paint.setPathEffect(SkPath1DPathEffect::Make(path, this->getWidth(), 0.0f, SkPath1DPathEffect::kRotate_Style));
        }

        if (this->style == BorderStyle::Dashed) {
            const SkScalar intervals[] = {10.0f, 5.0f};
            paint.setPathEffect(SkDashPathEffect::Make(intervals, 2, 0.0f));
        }

        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        float radiusX = this->radiusX * ctx->getPixelScale();
        float radiusY = this->radiusY * ctx->getPixelScale();
        SkRRect skRRect = SkRRect::MakeRectXY(skRect, radiusX, radiusY);

        canvas->drawRRect(skRRect, paint);
    }

    std::vector <RenderElement> Border::getChildren(ApplicationContext *ctx, Window *window, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();

            float borderWidth = this->getWidth() * ctx->getPixelScale();
            child.position = {borderWidth, borderWidth};

            float childWidth = size.width - 2 * borderWidth;
            float childHeight = size.height - 2 * borderWidth;
            child.size = {childWidth, childHeight};

            children.push_back(child);
        }

        return children;
    }
}

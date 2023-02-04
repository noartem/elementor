//
// Created by noartem on 21.04.2022.
//

#include "Rounded.h"

#include <include/core/SkRRect.h>

namespace elementor::elements {
    Rounded *rounded() {
        return new Rounded();
    }

    Rounded *
    Rounded::setRadius(float radiusTopLeft, float radiusTopRight, float radiusBottomRight, float radiusBottomLeft) {
        this->radiusTopLeft = radiusTopLeft;
        this->radiusTopRight = radiusTopRight;
        this->radiusBottomLeft = radiusBottomLeft;
        this->radiusBottomRight = radiusBottomRight;
        return this;
    }

    Rounded *Rounded::setRadius(float radiusLeft, float radiusRight) {
        this->setRadius(radiusLeft, radiusRight, radiusRight, radiusLeft);
        return this;
    }

    Rounded *Rounded::setRadius(float radius) {
        this->setRadius(radius, radius);
        return this;
    }

    float Rounded::getRadiusTopLeft() {
        return this->radiusTopLeft;
    }

    float Rounded::getRadiusTopRight() {
        return this->radiusTopRight;
    }

    float Rounded::getRadiusBottomLeft() {
        return this->radiusBottomLeft;
    }

    float Rounded::getRadiusBottomRight() {
        return this->radiusBottomRight;
    }

    Rounded *Rounded::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    void Rounded::paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) {
        float topLeft = this->getRadiusTopLeft() * ctx->getPixelScale();
        float topRight = this->getRadiusTopRight() * ctx->getPixelScale();
        float bottomRight = this->getRadiusBottomRight() * ctx->getPixelScale();
        float bottomLeft = this->getRadiusBottomLeft() * ctx->getPixelScale();
        SkVector corners[] = {{topLeft,     topLeft},
                              {topRight,    topRight},
                              {bottomRight, bottomRight},
                              {bottomLeft,  bottomLeft}};

        SkRRect skRRect;
        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        skRRect.setRectRadii(skRect, corners);

        canvas->clipRRect(skRRect, SkClipOp::kIntersect, true);
    }

    Size Rounded::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.max;
        }
    }

    std::vector<RenderElement> Rounded::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector<RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }

    ClipBehavior Rounded::getClipBehaviour() {
        return ClipBehavior::AntiAlias;
    }
}

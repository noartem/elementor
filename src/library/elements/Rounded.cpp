//
// Created by noartem on 21.04.2022.
//

#include "Rounded.h"

#include <include/core/SkRRect.h>

namespace elementor::elements {
    Rounded *rounded() {
        return new Rounded();
    }

    Rounded *Rounded::setRadius(float radiusTopLeft, float radiusTopRight, float radiusBottomRight, float radiusBottomLeft) {
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

    void Rounded::paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) {
        float topLeft = this->getRadiusTopLeft() * ctx->window->monitorPixelScale;
        float topRight = this->getRadiusTopRight() * ctx->window->monitorPixelScale;
        float bottomRight = this->getRadiusBottomRight() * ctx->window->monitorPixelScale;
        float bottomLeft = this->getRadiusBottomLeft() * ctx->window->monitorPixelScale;
        SkVector corners[] = {{topLeft, topLeft}, {topRight, topRight}, {bottomRight, bottomRight}, {bottomLeft, bottomLeft}};

        SkRRect skRRect;
        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        skRRect.setRectRadii(skRect, corners);

        canvas->clipRRect(skRRect, SkClipOp::kIntersect, true);
    }

    Size Rounded::getSize(ApplicationContext *ctx, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, boundaries);
        } else {
            return boundaries.max;
        }
    }

    std::vector <RenderElement> Rounded::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.size = size;
            child.position = {0, 0};

            children.push_back(child);
        }

        return children;
    }

    ClipBehavior Rounded::getClipBehaviour() {
        return ClipBehavior::AntiAlias;
    }
}

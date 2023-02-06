//
// Created by noartem on 21.04.2022.
//

#include "Rounded.h"

#include <include/core/SkRRect.h>

namespace elementor::elements {
    std::shared_ptr<Rounded> rounded() {
        return std::make_shared<Rounded>();
    }

    std::shared_ptr<Rounded> Rounded::setRadius(float radiusTopLeft, float radiusTopRight, float radiusBottomRight, float radiusBottomLeft) {
        this->radiusTopLeft = radiusTopLeft;
        this->radiusTopRight = radiusTopRight;
        this->radiusBottomLeft = radiusBottomLeft;
        this->radiusBottomRight = radiusBottomRight;
        return shared_from_this();
    }

    std::shared_ptr<Rounded> Rounded::setRadius(float radiusLeft, float radiusRight) {
        this->setRadius(radiusLeft, radiusRight, radiusRight, radiusLeft);
        return shared_from_this();
    }

    std::shared_ptr<Rounded> Rounded::setRadius(float radius) {
        this->setRadius(radius, radius);
        return shared_from_this();
    }

    float Rounded::getRadiusTopLeft() const {
        return this->radiusTopLeft;
    }

    float Rounded::getRadiusTopRight() const {
        return this->radiusTopRight;
    }

    float Rounded::getRadiusBottomLeft() const {
        return this->radiusBottomLeft;
    }

    float Rounded::getRadiusBottomRight() const {
        return this->radiusBottomRight;
    }

    std::shared_ptr<Rounded> Rounded::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    void Rounded::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) {
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

    Size Rounded::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild()->getSize(ctx, window, boundaries);
        } else {
            return boundaries.max;
        }
    }

    std::vector<RenderElement> Rounded::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
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

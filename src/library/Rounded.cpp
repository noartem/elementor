//
// Created by noartem on 21.04.2022.
//

#include "Rounded.h"

#include <include/core/SkRRect.h>

namespace elementor {
    Rounded *rounded() {
        return new Rounded();
    }

    Rounded *Rounded::setRadius(float radiusX, float radiusY) {
        this->radiusX = radiusX;
        this->radiusY = radiusY;
        return this;
    }

    Rounded *Rounded::setRadius(float radiusXY) {
        this->setRadius(radiusXY, radiusXY);
        return this;
    }

    float Rounded::getRadiusX() {
        return this->radiusX;
    }

    float Rounded::getRadiusY() {
        return this->radiusY;
    }

    Rounded *Rounded::setChild(Element *child) {
        child->context = context;
        this->updateChild(child);
        return this;
    }

    void Rounded::paintBackground(SkCanvas *canvas, ElementRect rect) {
        SkRect skRect = SkRect::MakeXYWH(0, 0, rect.size.width, rect.size.height);
        float radiusX = this->radiusX * this->context->monitorPixelScale;
        float radiusY = this->radiusY * this->context->monitorPixelScale;
        SkRRect skRRect = SkRRect::MakeRectXY(skRect, radiusX, radiusY);

        canvas->clipRRect(skRRect, SkClipOp::kIntersect, true);
    }

    Size Rounded::getSize(Boundaries boundaries) {
        if (this->hasChild()) {
            return this->getChild(this->context)->getSize(boundaries);
        } else {
            return boundaries.max;
        }
    }

    std::vector <RenderElement> Rounded::getRenderChildren(Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild(this->context);
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

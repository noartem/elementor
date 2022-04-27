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

    void Rounded::paintBackground(SkCanvas *canvas, RenderSize size) {
        SkRRect oval = SkRRect::MakeRectXY(
            SkRect::MakeXYWH(0, 0, size.width, size.height),
            this->radiusX * this->context->monitorPixelScale,
            this->radiusY * this->context->monitorPixelScale
        );

        canvas->clipRRect(oval, SkClipOp::kIntersect, true);
    }

    std::vector <RenderElement> Rounded::getChildren(RenderSize size) {
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
}

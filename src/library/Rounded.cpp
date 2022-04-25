//
// Created by noartem on 21.04.2022.
//

#include "Rounded.h"

#include <include/core/SkRRect.h>

#include <iostream>

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
        this->updateChild(child);
        return this;
    }

    std::shared_ptr <ElementRenderer> Rounded::render() {
        return std::make_shared<RoundedRenderer>(this->context, this->getRadiusX(), this->getRadiusY(), this->getChild());
    }

    RoundedRenderer::RoundedRenderer(ApplicationContext *context, float radiusX, float radiusY, Element *child) {
        this->context = context;
        this->radiusX = radiusX * this->context->monitorPixelScale;
        this->radiusY = radiusY * this->context->monitorPixelScale;
        this->child = child;
    }

    void RoundedRenderer::paintBackground(SkCanvas *canvas, RenderSize size) {
        SkRect paintRect = SkRect::MakeXYWH(0, 0, size.width, size.height);
        SkRRect oval = SkRRect::MakeRectXY(paintRect, this->radiusX, this->radiusY);
        canvas->clipRRect(oval, SkClipOp::kIntersect, true);
    }

    std::vector <RenderElement> RoundedRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement child;
            child.element = this->child;
            child.element->context = context;
            child.renderer = this->child->render();
            child.size = size;
            child.position = {0, 0};

            children.push_back(child);
        }

        return children;
    }
}

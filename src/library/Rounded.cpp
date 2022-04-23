//
// Created by noartem on 21.04.2022.
//

#include "Rounded.h"

#include <include/core/SkRRect.h>

namespace elementor {
    Rounded::Rounded(Element *child) {
        this->setChild(child);
    }

    Rounded::Rounded(float radiusXY, Element *child) {
        this->setRadius(radiusXY);
        this->setChild(child);
    }

    Rounded::Rounded(float radiusX, float radiusY, Element *child) {
        this->setRadius(radiusX, radiusY);
        this->setChild(child);
    }

    void Rounded::setRadius(float radiusXY) {
        this->radiusX = radiusXY;
        this->radiusY = radiusXY;
    }

    void Rounded::setRadius(float radiusX, float radiusY) {
        this->radiusX = radiusX;
        this->radiusY = radiusY;
    }

    float Rounded::getRadiusX() {
        return this->radiusX;
    }

    float Rounded::getRadiusY() {
        return this->radiusY;
    }

    std::shared_ptr <ElementRenderer> Rounded::render() {
        return std::make_shared<RoundedRenderer>(this->context, this->radiusX, this->radiusY, this->getChild());
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

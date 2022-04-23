//
// Created by noartem on 21.04.2022.
//

#include "ClipRRect.h"

#include <include/core/SkRRect.h>

namespace elementor {
    ClipRRect::ClipRRect(Element *child) {
        this->setChild(child);
    }

    ClipRRect::ClipRRect(float radiusXY, Element *child) {
        this->radiusX = radiusXY;
        this->radiusY = radiusXY;
        this->setChild(child);
    }

    ClipRRect::ClipRRect(float radiusXY, SkClipOp clipOp, Element *child) {
        this->radiusX = radiusXY;
        this->radiusY = radiusXY;
        this->clipOp = clipOp;
        this->setChild(child);
    }

    ClipRRect::ClipRRect(float radiusX, float radiusY, Element *child) {
        this->radiusX = radiusX;
        this->radiusY = radiusY;
        this->setChild(child);
    }

    ClipRRect::ClipRRect(float radiusX, float radiusY, SkClipOp clipOp, Element *child) {
        this->radiusX = radiusX;
        this->radiusY = radiusY;
        this->clipOp = clipOp;
        this->setChild(child);
    }

    std::shared_ptr <ElementRenderer> ClipRRect::render() {
        return std::make_shared<ClipRRectRenderer>(this->context, this->radiusX, this->radiusY, this->clipOp, this->getChild());
    }

    ClipRRectRenderer::ClipRRectRenderer(ApplicationContext *context, float radiusX, float radiusY, SkClipOp clipOp, Element *child) {
        this->context = context;
        this->radiusX = radiusX * this->context->monitorPixelScale;
        this->radiusY = radiusY * this->context->monitorPixelScale;
        this->clipOp = clipOp;
        this->child = child;
    }

    void ClipRRectRenderer::paintBackground(SkCanvas *canvas, RenderSize size) {
        SkRect paintRect = SkRect::MakeXYWH(0, 0, size.width, size.height);
        SkRRect oval = SkRRect::MakeRectXY(paintRect, this->radiusX, this->radiusY);
        canvas->clipRRect(oval, this->clipOp, true);
    }

    std::vector <RenderElement> ClipRRectRenderer::getChildren(RenderSize size) {
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

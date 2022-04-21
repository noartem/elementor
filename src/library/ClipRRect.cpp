//
// Created by noartem on 21.04.2022.
//

#include "ClipRRect.h"

#include <include/core/SkRRect.h>

namespace elementor {
    std::shared_ptr <ElementRenderer> ClipRRect::render() {
        auto renderer = std::make_shared<ClipRRectRenderer>();
        renderer->child = this->child;
        renderer->radius = this->radius;
        renderer->clipOp = this->clipOp;
        renderer->context = this->context;
        return renderer;
    }

    void ClipRRectRenderer::paintBackground(SkCanvas *canvas, RenderPosition start, RenderSize size) {
        SkRect paintRect = SkRect::MakeXYWH(start.x, start.y, size.width, size.height);
        int radius = this->radius * this->context->monitorPixelScale;
        SkRRect oval = SkRRect::MakeRectXY(paintRect, radius, radius);
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

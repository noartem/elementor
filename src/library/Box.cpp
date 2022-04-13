//
// Created by noartem on 13.04.2022.
//

#include "Box.h"

namespace elementor {
    IElementRenderer* Box::render() {
        BoxRenderer *boxRenderer = new BoxRenderer();
        boxRenderer->paddings = this->paddings;
        boxRenderer->child = this->child;

        IElementRenderer *renderer = boxRenderer;
        return renderer;
    }

    RenderSize BoxRenderer::getSize(Boundaries boundaries) {
        if (boundaries.max.height != -1 && boundaries.max.width != -1) {
            return boundaries.max;
        } else {
            return boundaries.min;
        }
    }

    void BoxRenderer::paintBackground(RenderSize size, SkCanvas *canvas) {
    }

    std::vector <RenderChild> BoxRenderer::getChildren(RenderSize size) {
        std::vector<RenderChild> children;

        if (this->child) {
            RenderChild renderChild;
            renderChild.element = this->child;

            if (this->paddings) {
                renderChild.position = {(float) this->paddings, (float) this->paddings};
                renderChild.size = {size.width - this->paddings, size.height - this->paddings};
            } else {
                renderChild.position = {0, 0};
                renderChild.size = size;
            }

            children.push_back(renderChild);
        }

        return children;
    }
}

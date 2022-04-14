//
// Created by noartem on 13.04.2022.
//

#include "Padding.h"

namespace elementor {
    void Padding::setPaddings(int paddingYX) {
        this->paddings = {paddingYX, paddingYX, paddingYX, paddingYX};
    }
    
    void Padding::setPaddings(int paddingY, int paddingX) {
        this->paddings = {paddingY, paddingX, paddingY, paddingX};
    }
    
    void Padding::setPaddings(int paddingTop, int paddingX, int paddingBottom) {
        this->paddings = {paddingTop, paddingX, paddingBottom, paddingX};
    }

    void Padding::setPaddings(int paddingTop, int paddingRight, int paddingBottom, int paddingLeft) {
        this->paddings = {paddingTop, paddingLeft, paddingBottom, paddingRight};
    }

    IElementRenderer* Padding::render() {
        PaddingRenderer *paddingRenderer = new PaddingRenderer();
        paddingRenderer->paddings = this->paddings;
        paddingRenderer->child = this->child;

        IElementRenderer *renderer = paddingRenderer;
        return renderer;
    }

    RenderSize PaddingRenderer::getSize(Boundaries boundaries) {
        if (boundaries.max.height != -1 && boundaries.max.width != -1) {
            return boundaries.max;
        } else {
            return boundaries.min;
        }
    }

    void PaddingRenderer::paintBackground(RenderSize size, SkCanvas *canvas) {
    }

    std::vector <RenderChild> PaddingRenderer::getChildren(RenderSize size) {
        std::vector<RenderChild> children;

        if (this->child) {
            RenderChild renderChild;
            renderChild.element = this->child;

            renderChild.position = {
                (float) this->paddings.left,
                (float) this->paddings.top,
            };

            renderChild.size = {
                size.width - (this->paddings.left + this->paddings.right),
                size.height - (this->paddings.top + this->paddings.bottom),
            };

            children.push_back(renderChild);
        }

        return children;
    }
}

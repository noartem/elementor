//
// Created by noartem on 16.04.2022.
//

#include "Element.h"

namespace elementor {
    std::unique_ptr<ElementRenderer> Element::render() {
        auto renderer = std::make_unique<ElementRenderer>();
        return renderer;
    }

    RenderSize ElementRenderer::getSize(RenderBoundaries boundaries) {
        return boundaries.max;
    }

    void ElementRenderer::paintBackground(SkCanvas *canvas, RenderPosition start, RenderSize size) {
    }

    std::vector <RenderChild> ElementRenderer::getChildren(RenderSize size) {
        std::vector<RenderChild> children;
        return children;
    }
}

//
// Created by noartem on 13.04.2022.
//

#include "Sized.h"

#include <algorithm>

namespace elementor {
    std::shared_ptr <ElementRenderer> Sized::render() {
        auto renderer = std::make_shared<SizedRenderer>();
        renderer->width = this->width;
        renderer->height = this->height;
        renderer->child = this->child;
        renderer->context = this->context;
        return renderer;
    }

    RenderSize SizedRenderer::getSize(RenderBoundaries boundaries) {
        int sizeWidth = this->width * this->context->monitorPixelScale;
        int width = std::min(std::max(sizeWidth, boundaries.min.width), boundaries.max.width);
        int sizeHeight = this->height * this->context->monitorPixelScale;
        int height = std::min(std::max(sizeHeight, boundaries.min.height), boundaries.max.height);
        return {width, height};
    }

    std::vector <RenderElement> SizedRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement child;
            child.element = this->child;
            child.element->context = context;
            child.renderer = this->child->render();
            child.position = {0, 0};
            child.size = size;

            children.push_back(child);
        }

        return children;
    }
}

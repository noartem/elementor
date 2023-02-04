//
// Created by noartem on 13.04.2022.
//

#include "Height.h"

namespace elementor::elements {
    Height *height() {
        return new Height();
    }

    Height *Height::setHeight(float height) {
        this->height = height;
        return this;
    }

    float Height::getHeight() {
        return this->height;
    }

    Height *Height::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Height::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        float height = this->height * ctx->getPixelScale();
        if (this->hasChild()) {
            Boundaries childBoundaries = {{boundaries.min.width, std::max(height, boundaries.min.height)}, {boundaries.max.width, std::min(height, boundaries.max.height)}};
            return this->getChild()->getSize(ctx, window, childBoundaries);
        } else {
            return fitSizeInBoundaries({boundaries.max.width, height}, boundaries);
        }
    }

    std::vector <RenderElement> Height::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }
}

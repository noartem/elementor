//
// Created by noartem on 13.04.2022.
//

#include "Width.h"

namespace elementor::elements {
    Width *width() {
        return new Width();
    }

    Width *Width::setWidth(float width) {
        this->width = width;
        return this;
    }

    float Width::getWidth() {
        return this->width;
    }

    Width *Width::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size Width::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        float width = this->width * ctx->getPixelScale();
        if (this->hasChild()) {
            Boundaries childBoundaries = {{std::max(width, boundaries.min.width), boundaries.min.height}, {std::min(width, boundaries.max.width), boundaries.max.height}};
            return this->getChild()->getSize(ctx, window, childBoundaries);
        } else {
            return fitSizeInBoundaries({width, boundaries.max.height}, boundaries);
        }
    }

    std::vector <RenderElement> Width::getChildren(ApplicationContext *ctx, Window *window, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.position = {0, 0};
            child.size = size;

            children.push_back(child);
        }

        return children;
    }
}

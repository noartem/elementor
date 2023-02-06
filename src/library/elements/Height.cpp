//
// Created by noartem on 13.04.2022.
//

#include "Height.h"

namespace elementor::elements {
    std::shared_ptr<Height> height() {
        return std::make_shared<Height>();
    }

    std::shared_ptr<Height> Height::setHeight(float height) {
        this->height = height;
        return shared_from_this();
    }

    float Height::getHeight() {
        return this->height;
    }

    std::shared_ptr<Height> Height::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size
    Height::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        float height = this->height * ctx->getPixelScale();
        if (this->hasChild()) {
            Boundaries childBoundaries = {{boundaries.min.width, std::max(height, boundaries.min.height)},
                                          {boundaries.max.width, std::min(height, boundaries.max.height)}};
            return this->getChild()->getSize(ctx, window, childBoundaries);
        } else {
            return fitSizeInBoundaries({boundaries.max.width, height}, boundaries);
        }
    }

    std::vector<RenderElement>
    Height::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector<RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }
}

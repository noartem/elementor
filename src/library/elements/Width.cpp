//
// Created by noartem on 13.04.2022.
//

#include "Width.h"

namespace elementor::elements {
    std::shared_ptr<Width> width() {
        return std::make_shared<Width>();
    }

    std::shared_ptr<Width> Width::setWidth(float width) {
        this->width = width;
        return shared_from_this();
    }

    float Width::getWidth() {
        return this->width;
    }

    std::shared_ptr<Width> Width::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    Size Width::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        float width = this->width * ctx->getPixelScale();
        if (this->hasChild()) {
            Boundaries childBoundaries = {{std::max(width, boundaries.min.width), boundaries.min.height}, {std::min(width, boundaries.max.width), boundaries.max.height}};
            return this->getChild()->getSize(ctx, window, childBoundaries);
        } else {
            return fitSizeInBoundaries({width, boundaries.max.height}, boundaries);
        }
    }

    std::vector <RenderElement> Width::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement childElement{this->getChild(), {0, 0}, rect.size};
            children.push_back(childElement);
        }

        return children;
    }
}

//
// Created by noartem on 04.05.2022.
//

#include "SizedAbsolute.h"

namespace elementor {
    SizedAbsolute *sizedAbsolute() {
        return new SizedAbsolute();
    }

    SizedAbsolute *SizedAbsolute::setWidth(int width) {
        this->width = (float) width;
        return this;
    }

    SizedAbsolute *SizedAbsolute::setHeight(int height) {
        this->height = height;
        return this;
    }

    SizedAbsolute *SizedAbsolute::setSize(int width, int height) {
        this->setWidth(width);
        this->setHeight(height);
        return this;
    }

    SizedAbsolute *SizedAbsolute::setSize(int size) {
        this->setSize(size, size);
        return this;
    }

    int SizedAbsolute::getWidth() {
        return this->width;
    }

    int SizedAbsolute::getHeight() {
        return this->height;
    }

    SizedAbsolute *SizedAbsolute::setChild(Element *child) {
        child->context = context;
        this->updateChild(child);
        return this;
    }

    RenderSize SizedAbsolute::getSize(RenderBoundaries boundaries) {
        int width = this->width == -1 ? boundaries.max.width : this->getWidth();
        int height = this->height == -1 ? boundaries.max.height : this->getHeight();
        return fitSizeInBoundaries({width, height}, boundaries);
    }

    std::vector <RenderElement> SizedAbsolute::getRenderChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild(this->context);
            child.position = {0, 0};
            child.size = size;

            children.push_back(child);
        }

        return children;
    }
}

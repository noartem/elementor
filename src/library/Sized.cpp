//
// Created by noartem on 13.04.2022.
//

#include "Sized.h"

namespace elementor {
    Sized *sized() {
        return new Sized();
    }

    Sized *Sized::setWidth(float width) {
        this->width = width;
        this->absWidth = false;
        return this;
    }

    Sized *Sized::setWidth(int width) {
        this->width = (float) width;
        this->absWidth = true;
        return this;
    }

    Sized *Sized::setHeight(float height) {
        this->height = height;
        return this;
    }

    Sized *Sized::setHeight(int height) {
        this->height = height;
        this->absHeight = true;
        return this;
    }

    Sized *Sized::setSize(float width, float height) {
        this->setWidth(width);
        this->setHeight(height);
        return this;
    }

    Sized *Sized::setSize(int width, int height) {
        this->setWidth(width);
        this->setHeight(height);
        return this;
    }

    Sized *Sized::setSize(float size) {
        this->setSize(size, size);
        return this;
    }

    Sized *Sized::setSize(int size) {
        this->setSize(size, size);
        return this;
    }

    float Sized::getWidth() {
        return this->width;
    }

    float Sized::getHeight() {
        return this->height;
    }

    Sized *Sized::setChild(Element *child) {
        child->context = context;
        this->updateChild(child);
        return this;
    }

    RenderSize Sized::getSize(RenderBoundaries boundaries) {
        int width = this->width == -1 ? boundaries.max.width : this->absWidth ? (int) this->width : ceil(this->width * this->context->monitorPixelScale);
        int height = this->height == -1 ? boundaries.max.height : this->absHeight ? (int) this->height : ceil(this->height * this->context->monitorPixelScale);
        return fitSizeInBoundaries({width, height}, boundaries);
    }

    std::vector <RenderElement> Sized::getRenderChildren(RenderSize size) {
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

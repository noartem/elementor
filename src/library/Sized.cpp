//
// Created by noartem on 13.04.2022.
//

#include "Sized.h"

#include <algorithm>

namespace elementor {
    Sized *sized() {
        return new Sized();
    }

    Sized *Sized::setWidth(float width) {
        this->width = width;
        return this;
    }

    Sized *Sized::setHeight(float height) {
        this->height = height;
        return this;
    }

    Sized *Sized::setSize(float width, float height) {
        this->setWidth(width);
        this->setHeight(height);
        return this;
    }

    Sized *Sized::setSize(float size) {
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
        this->updateChild(child);
        return this;
    }

    std::shared_ptr <ElementRenderer> Sized::render() {
        return std::make_shared<SizedRenderer>(this->context, this->getWidth(), this->getHeight(), this->getChild());
    }

    SizedRenderer::SizedRenderer(ApplicationContext *context, float width, float height, Element *child) {
        this->context = context;
        this->width = width * this->context->monitorPixelScale;
        this->height = height * this->context->monitorPixelScale;
        this->child = child;
    }

    RenderSize SizedRenderer::getSize(RenderBoundaries boundaries) {
        int width = std::min(std::max(this->width, boundaries.min.width), boundaries.max.width);
        int height = std::min(std::max(this->height, boundaries.min.height), boundaries.max.height);
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

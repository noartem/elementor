//
// Created by noartem on 13.04.2022.
//

#include "Padding.h"

namespace elementor {

    Padding::Padding(Element *child) {
        this->setChild(child);
    }

    Padding::Padding(float paddings, Element *child) {
        this->setPaddings(paddings);
        this->setChild(child);
    }

    Padding::Padding(float paddingY, float paddingX, Element *child) {
        this->setPaddings(paddingY, paddingX);
        this->setChild(child);
    }

    Padding::Padding(float paddingTop, float paddingX, float paddingBottom, Element *child) {
        this->setPaddings(paddingTop, paddingX, paddingBottom);
        this->setChild(child);
    }

    Padding::Padding(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft, Element *child) {
        this->setPaddings(paddingTop, paddingRight, paddingBottom, paddingLeft);
        this->setChild(child);
    }

    void Padding::setPaddings(float paddingYX) {
        this->paddings = {paddingYX, paddingYX, paddingYX, paddingYX};
    }

    void Padding::setPaddings(float paddingY, float paddingX) {
        this->paddings = {paddingY, paddingX, paddingY, paddingX};
    }

    void Padding::setPaddings(float paddingTop, float paddingX, float paddingBottom) {
        this->paddings = {paddingTop, paddingX, paddingBottom, paddingX};
    }

    void Padding::setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft) {
        this->paddings = {paddingTop, paddingLeft, paddingBottom, paddingRight};
    }

    std::shared_ptr <ElementRenderer> Padding::render() {
        return std::make_shared<PaddingRenderer>(this->context, this->paddings, this->getChild());
    }

    PaddingRenderer::PaddingRenderer(ApplicationContext *context, PaddingsValue paddings, Element *child) {
        this->context = context;
        this->paddings = {
            (int) ceil(paddings.top * this->context->monitorPixelScale),
            (int) ceil(paddings.right * this->context->monitorPixelScale),
            (int) ceil(paddings.bottom * this->context->monitorPixelScale),
            (int) ceil(paddings.left * this->context->monitorPixelScale),
        };
        this->child = child;
    }

    std::vector <RenderElement> PaddingRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement child;
            child.element = this->child;
            child.element->context = context;
            child.renderer = this->child->render();

            child.position = {this->paddings.left, this->paddings.top};

            int childWidth = size.width - (this->paddings.left + this->paddings.right);
            int childHeight = size.height - (this->paddings.top + this->paddings.bottom);
            child.size = {childWidth, childHeight};

            children.push_back(child);
        }

        return children;
    }
}

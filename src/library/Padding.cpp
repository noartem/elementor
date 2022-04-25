//
// Created by noartem on 13.04.2022.
//

#include "Padding.h"

namespace elementor {
    Padding *padding() {
        return new Padding();
    }

    Padding *Padding::setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft) {
        this->paddings = {paddingTop, paddingLeft, paddingBottom, paddingRight};
        return this;
    }

    Padding *Padding::setPaddings(float paddingTop, float paddingX, float paddingBottom) {
        this->setPaddings(paddingTop, paddingX, paddingBottom, paddingX);
        return this;
    }

    Padding *Padding::setPaddings(float paddingY, float paddingX) {
        this->setPaddings(paddingY, paddingX, paddingY, paddingX);
        return this;
    }

    Padding *Padding::setPaddings(float paddingYX) {
        this->setPaddings(paddingYX, paddingYX, paddingYX, paddingYX);
        return this;
    }

    PaddingsValue Padding::getPaddings() {
        return this->paddings;
    }

    Padding *Padding::setChild(Element *child) {
        this->updateChild(child);
        return this;
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

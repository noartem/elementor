//
// Created by noartem on 13.04.2022.
//

#include "Padding.h"

namespace elementor {
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
        auto renderer = std::make_shared<PaddingRenderer>();
        renderer->paddings = this->paddings;
        renderer->child = this->child;
        renderer->context = this->context;
        return renderer;
    }

    std::vector <RenderElement> PaddingRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        int paddingsTop = this->paddings.top * this->context->monitorPixelScale;
        int paddingsRight = this->paddings.right * this->context->monitorPixelScale;
        int paddingsBottom = this->paddings.bottom * this->context->monitorPixelScale;
        int paddingsLeft = this->paddings.left * this->context->monitorPixelScale;

        if (this->child) {
            RenderElement child;
            child.element = this->child;
            child.element->context = context;
            child.renderer = this->child->render();

            child.position = {paddingsLeft, paddingsTop};

            int childWidth = size.width - (paddingsLeft + paddingsRight);
            int childHeight = size.height - (paddingsTop + paddingsBottom);
            child.size = {childWidth, childHeight};

            children.push_back(child);
        }

        return children;
    }
}

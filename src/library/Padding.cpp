//
// Created by noartem on 13.04.2022.
//

#include "Padding.h"

namespace elementor {
    void Padding::setPaddings(int paddingYX) {
        this->paddings = {paddingYX, paddingYX, paddingYX, paddingYX};
    }

    void Padding::setPaddings(int paddingY, int paddingX) {
        this->paddings = {paddingY, paddingX, paddingY, paddingX};
    }

    void Padding::setPaddings(int paddingTop, int paddingX, int paddingBottom) {
        this->paddings = {paddingTop, paddingX, paddingBottom, paddingX};
    }

    void Padding::setPaddings(int paddingTop, int paddingRight, int paddingBottom, int paddingLeft) {
        this->paddings = {paddingTop, paddingLeft, paddingBottom, paddingRight};
    }

    std::unique_ptr <ElementRenderer> Padding::render() {
        auto renderer = std::make_unique<PaddingRenderer>();
        renderer->paddings = this->paddings;
        renderer->child = this->child;
        return renderer;
    }

    std::vector <RenderElement> PaddingRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement child;
            child.element = this->child;

            child.position = {this->paddings.left, this->paddings.top};

            int childWidth = size.width - (this->paddings.left + this->paddings.right);
            int childHeight = size.height - (this->paddings.top + this->paddings.bottom);
            child.size = {childWidth, childHeight};

            children.push_back(child);
        }

        return children;
    }
}

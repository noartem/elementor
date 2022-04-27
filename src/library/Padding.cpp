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
        child->context = context;
        this->updateChild(child);
        return this;
    }

    std::vector <RenderElement> Padding::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild(this->context);

            int paddingsTop = (int) ceil(this->paddings.top * this->context->monitorPixelScale);
            int paddingsRight = (int) ceil(this->paddings.right * this->context->monitorPixelScale);
            int paddingsBottom = (int) ceil(this->paddings.bottom * this->context->monitorPixelScale);
            int paddingsLeft = (int) ceil(this->paddings.left * this->context->monitorPixelScale);

            child.position = {paddingsLeft, paddingsTop};

            int childWidth = size.width - (paddingsLeft + paddingsRight);
            int childHeight = size.height - (paddingsTop + paddingsBottom);
            child.size = {childWidth, childHeight};

            children.push_back(child);
        }

        return children;
    }
}

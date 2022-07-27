//
// Created by noartem on 27.07.2022.
//

#include "FitCover.h"

namespace elementor::elements {
    FitCover *fitCover() {
        return new FitCover();
    }

    FitCover *FitCover::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    ClipBehavior FitCover::getClipBehaviour() {
        return ClipBehavior::AntiAlias;
    }

    std::vector <RenderElement> FitCover::getChildren(ApplicationContext *ctx, Size size) {
        RenderElement child;
        child.element = this->getChild();

        Size childSize = child.element->getSize(ctx, {{0, 0}, {INFINITY, INFINITY}});
        float ratio = childSize.width / childSize.height;
        if (size.width > size.height) {
            child.size.width = size.width;
            child.size.height = size.width / ratio;
        } else {
            child.size.height = size.height;
            child.size.width = size.height / ratio;
        }

        child.position.x = (size.width - child.size.width) / 2;
        child.position.y = (size.height - child.size.height) / 2;

        return {child};
    }
}

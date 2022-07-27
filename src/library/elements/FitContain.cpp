//
// Created by noartem on 27.07.2022.
//

#include "FitContain.h"

namespace elementor::elements {
    FitContain *fitContain() {
        return new FitContain();
    }

    FitContain *FitContain::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    Size fitSizeWithin(Size inner, Size outer) {
        float innerRatio = inner.width / inner.height;
        float outerRatio = outer.width / outer.height;
        float resizeFactor = (innerRatio >= outerRatio) ? (outer.width / inner.width) : (outer.height / inner.height);
        return {inner.width * resizeFactor, inner.height * resizeFactor};
    }

    std::vector <RenderElement> FitContain::getChildren(ApplicationContext *ctx, Size size) {
        RenderElement child;
        child.element = this->getChild();
        Size childSize = child.element->getSize(ctx, {{0, 0}, {INFINITY, INFINITY}});
        child.size = fitSizeWithin(childSize, size);
        child.position.x = (size.width - child.size.width) / 2;
        child.position.y = (size.height - child.size.height) / 2;
        return {child};
    }
}

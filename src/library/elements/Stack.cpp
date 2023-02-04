//
// Created by noartem on 03.02.2022.
//

#include "Stack.h"

namespace elementor::elements {
    Stack *stack() {
        return new Stack();
    }

    Stack *Stack::appendChild(Element *child) {
        this->addChild(child);
        return this;
    }

    Size Stack::getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) {
        Size size{0, 0};
        for (auto child: this->getChildrenList()) {
            Size childSize = child->getSize(ctx, window, boundaries);
            size.width = std::max(size.height, childSize.width);
            size.height = std::max(size.height, childSize.height);
        }
        return fitSizeInBoundaries(size, boundaries);
    }

    std::vector<RenderElement> Stack::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector<RenderElement> children;

        for (auto child: this->getChildrenList()) {
            RenderElement childElement{};
            childElement.element = child;
            childElement.position = {0, 0};
            childElement.size = childElement.element->getSize(ctx, window, {{0, 0}, rect.size});
            children.push_back(childElement);
        }

        return children;
    }
}

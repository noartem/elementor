//
// Created by noartem on 03.02.2022.
//

#include "Stack.h"

namespace elementor::elements {
    std::shared_ptr<Stack> stack() {
        return std::make_shared<Stack>();
    }

    std::shared_ptr<Stack> Stack::appendChild(const std::shared_ptr<Element>& child) {
        this->addChild(child);
        return shared_from_this();
    }

    Size Stack::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        Size size{0, 0};
        for (const auto& child: this->getChildrenList()) {
            Size childSize = child->getSize(ctx, window, boundaries);
            size.width = std::max(size.height, childSize.width);
            size.height = std::max(size.height, childSize.height);
        }
        return fitSizeInBoundaries(size, boundaries);
    }

    std::vector<RenderElement> Stack::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector<RenderElement> children;

        for (const auto& child: this->getChildrenList()) {
            RenderElement childElement{};
            childElement.element = child;
            childElement.position = {0, 0};
            childElement.size = childElement.element->getSize(ctx, window, {{0, 0}, rect.size});
            children.push_back(childElement);
        }

        return children;
    }
}

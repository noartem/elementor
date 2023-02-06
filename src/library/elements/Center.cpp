//
// Created by noartem on 29.05.2022.
//

#include "Center.h"

#include <utility>

namespace elementor::elements {
    std::shared_ptr<Center> center() {
        return std::make_shared<Center>();
    }

    std::shared_ptr<Center> Center::setChild(const std::shared_ptr<Element>& child) {
        this->updateChild(child);
        return shared_from_this();
    }

    std::vector<RenderElement>
    Center::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        std::vector<RenderElement> children;

        if (this->hasChild()) {
            RenderElement child{};
            child.element = this->getChild();
            child.size = child.element->getSize(ctx, window, {{0, 0}, rect.size});
            child.position = {rect.size.width / 2 - child.size.width / 2, rect.size.height / 2 - child.size.height / 2};

            children.push_back(child);
        }

        return children;
    }
}

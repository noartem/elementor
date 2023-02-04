//
// Created by noartem on 29.05.2022.
//

#include "Center.h"

namespace elementor::elements {
    Center *center() {
        return new Center();
    }

    Center *Center::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    std::vector <RenderElement> Center::getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) {
        std::vector <RenderElement> children;

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

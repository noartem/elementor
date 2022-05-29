//
// Created by noartem on 29.05.2022.
//

#include "Center.h"

namespace elementor {
    Center *center() {
        return new Center();
    }

    Center *Center::setChild(Element *child) {
        this->updateChild(child);
        return this;
    }

    std::vector <RenderElement> Center::getChildren(ApplicationContext *ctx, Size size) {
        std::vector <RenderElement> children;

        if (this->hasChild()) {
            RenderElement child;
            child.element = this->getChild();
            child.size = child.element->getSize(ctx, {{size.width, }, size});
            child.position = {(int) ceil(size.width / 2.0 - child.size.width / 2.0), (int) ceil(size.height / 2.0 - child.size.height / 2.0)};

            children.push_back(child);
        }

        return children;
    }
}

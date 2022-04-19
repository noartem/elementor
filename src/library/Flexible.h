//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_FLEXIBLE_H
#define ELEMENTOR_FLEXIBLE_H

#include "Element.h"

namespace elementor {
    class Flexible : public Element {
    public:
        int grow = 1;
        Element *child;

        std::shared_ptr <ElementRenderer> render() override;
    };

    class FlexibleRenderer : public ElementRenderer {
    public:
        Element *child;

        std::vector <RenderElement> getChildren(RenderSize size) override;
    };
}


#endif //ELEMENTOR_FLEXIBLE_H

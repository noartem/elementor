//
// Created by noartem on 20.04.2022.
//

#ifndef ELEMENTOR_EXPANDED_H
#define ELEMENTOR_EXPANDED_H

#include "Element.h"

namespace elementor {
    class Expanded : public Element {
    public:
        int grow = 1;
        Element *child;

        std::shared_ptr <ElementRenderer> render() override;
    };

    class ExpandedRenderer : public ElementRenderer {
    public:
        Element *child;

        std::vector <RenderElement> getChildren(RenderSize size) override;
    };
}


#endif //ELEMENTOR_EXPANDED_H

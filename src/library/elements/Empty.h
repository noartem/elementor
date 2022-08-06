//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_EMPTY_H
#define ELEMENTOR_EMPTY_H

#include "../Element.h"

namespace elementor::elements {
    class Empty : public Element, public WithChild {
    public:
        Empty *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;
    };

    Empty *empty();
}


#endif //ELEMENTOR_EMPTY_H

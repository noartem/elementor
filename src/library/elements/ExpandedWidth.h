//
// Created by noartem on 18.06.2022.
//

#ifndef ELEMENTOR_EXPANDED_WIDTH_H
#define ELEMENTOR_EXPANDED_WIDTH_H

#include "../Element.h"

namespace elementor::elements {
    class ExpandedWidth : public Element, public WithChild {
    public:
        ExpandedWidth *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;  

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) override;
    };

    ExpandedWidth *expandedWidth();
}


#endif //ELEMENTOR_EXPANDED_WIDTH_H

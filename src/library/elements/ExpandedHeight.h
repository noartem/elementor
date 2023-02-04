//
// Created by noartem on 18.06.2022.
//

#ifndef ELEMENTOR_EXPANDED_HEIGHT_H
#define ELEMENTOR_EXPANDED_HEIGHT_H

#include "../Element.h"

namespace elementor::elements {
    class ExpandedHeight : public Element, public WithChild {
    public:
        ExpandedHeight *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;  

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) override;
    };

    ExpandedHeight *expandedHeight();
}


#endif //ELEMENTOR_EXPANDED_HEIGHT_H

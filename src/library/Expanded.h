//
// Created by noartem on 20.04.2022.
//

#ifndef ELEMENTOR_EXPANDED_H
#define ELEMENTOR_EXPANDED_H

#include "Element.h"

namespace elementor {
    class Expanded : public Element, public WithChild {
    public:
        Expanded *setGrow(int grow);

        int getGrow();

        Expanded *setChild(Element *child);

        std::shared_ptr <ElementRenderer> render() override;

    private:
        int grow = 1;
    };

    Expanded *expanded();

    class ExpandedRenderer : public ElementRenderer {
    public:
        ExpandedRenderer(ApplicationContext *context, Element *child);

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        Element *child;
    };
}


#endif //ELEMENTOR_EXPANDED_H

//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_FLEXIBLE_H
#define ELEMENTOR_FLEXIBLE_H

#include "../Element.h"

namespace elementor::elements {
    class Flexible : public Element, public WithChild {
    public:
        Flexible *setGrow(float grow);

        float getGrow();

        Flexible *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

    private:
        float grow = 1;
    };

    Flexible *flexible();
}


#endif //ELEMENTOR_FLEXIBLE_H

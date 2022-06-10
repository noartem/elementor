//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_FLEXIBLE_H
#define ELEMENTOR_FLEXIBLE_H

#include "../Element.h"

namespace elementor::elements {
    class Flexible : public Element, WithChild {
    public:
        Flexible *setGrow(float grow);

        float getGrow();

        Flexible *setChild(Element *child);

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

    private:
        float grow = 1;
    };

    Flexible *flexible();
}


#endif //ELEMENTOR_FLEXIBLE_H
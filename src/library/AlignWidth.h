//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_ALIGN_WIDTH_H
#define ELEMENTOR_ALIGN_WIDTH_H

#include "Element.h"

namespace elementor {
    class AlignWidth : public Element, WithChild {
    public:
        AlignWidth *setCoef(float coef, float childCoef);

        AlignWidth *setCoef(float coef);

        float getCoef();

        float getChildCoef();

        AlignWidth *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

    private:
        float coef = 0;
        float childCoef = 0;
    };

    AlignWidth *alignWidth();
}


#endif //ELEMENTOR_ALIGN_WIDTH_H

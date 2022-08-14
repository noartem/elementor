//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_ALIGN_HEIGHT_H
#define ELEMENTOR_ALIGN_HEIGHT_H

#include "../Element.h"

namespace elementor::elements {
    class AlignHeight : public Element, public WithChild {
    public:
        AlignHeight *setCoef(float coef, float childCoef);

        AlignHeight *setCoef(float coef);

        float getCoef();

        float getChildCoef();

        AlignHeight *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

    private:
        float coef = 0;
        float childCoef = 0;
    };

    AlignHeight *alignHeight();
}


#endif //ELEMENTOR_ALIGN_HEIGHT_H

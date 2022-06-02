//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_ALIGN_HEIGHT_H
#define ELEMENTOR_ALIGN_HEIGHT_H

#include "../Element.h"

namespace elementor::elements {
    class AlignHeight : public Element, WithChild {
    public:
        AlignHeight *setCoef(float coef, float childCoef);

        AlignHeight *setCoef(float coef);

        float getCoef();

        float getChildCoef();

        AlignHeight *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

    private:
        float coef = 0;
        float childCoef = 0;
    };

    AlignHeight *alignHeight();
}


#endif //ELEMENTOR_ALIGN_HEIGHT_H

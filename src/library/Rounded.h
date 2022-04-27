//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_ROUNDED_H
#define ELEMENTOR_ROUNDED_H

#include "Element.h"

namespace elementor {
    class Rounded : public Element, WithChild {
    public:
        Rounded *setRadius(float radiusX, float radiusY);

        Rounded *setRadius(float radiusXY);

        float getRadiusX();

        float getRadiusY();

        Rounded *setChild(Element *child);

        void paintBackground(SkCanvas *canvas, RenderSize size) override;

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        float radiusX = 10;
        float radiusY = 10;
    };

    Rounded *rounded();
}


#endif //ELEMENTOR_CLIP_H

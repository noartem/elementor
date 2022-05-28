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

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) override;

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Size size) override;

        ClipBehavior getClipBehaviour() override;

    private:
        float radiusX;
        float radiusY;
    };

    Rounded *rounded();
}


#endif //ELEMENTOR_CLIP_H

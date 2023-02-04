//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_ROUNDED_H
#define ELEMENTOR_ROUNDED_H

#include "../Element.h"

namespace elementor::elements {
    class Rounded : public Element, public WithChild {
    public:
        Rounded *setRadius(float radiusTopLeft, float radiusTopRight, float radiusBottomLeft, float radiusBottomRight);

        Rounded *setRadius(float radiusLeft, float radiusRight);

        Rounded *setRadius(float radius);

        float getRadiusTopLeft();

        float getRadiusTopRight();

        float getRadiusBottomLeft();

        float getRadiusBottomRight();

        Rounded *setChild(Element *child);

        void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) override;

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, ElementRect rect) override;

        ClipBehavior getClipBehaviour() override;

    private:
        float radiusTopLeft;
        float radiusTopRight;
        float radiusBottomLeft;
        float radiusBottomRight;
    };

    Rounded *rounded();
}


#endif //ELEMENTOR_CLIP_H

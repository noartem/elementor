//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_ROUNDED_H
#define ELEMENTOR_ROUNDED_H

#include "Element.h"

namespace elementor {
    class Rounded : public Element, public WithChild {
    public:
        Rounded() {};

        Rounded(Element *child);

        Rounded(float radiusXY, Element *child);

        Rounded(float radiusX, float radiusY, Element *child);

        void setRadius(float radiusXY);

        void setRadius(float radiusX, float radiusY);

        float getRadiusX();

        float getRadiusY();

        std::shared_ptr <ElementRenderer> render() override;

    private:
        float radiusX = 0;
        float radiusY = 0;
    };

    class RoundedRenderer : public ElementRenderer {
    public:
        RoundedRenderer(ApplicationContext *context, float radiusX, float radiusY, Element *child);

        void paintBackground(SkCanvas *canvas, RenderSize size) override;

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        int radiusX;
        int radiusY;
        Element *child;
    };
}


#endif //ELEMENTOR_CLIP_H

//
// Created by noartem on 27.04.2022.
//

#ifndef ELEMENTOR_BORDER_H
#define ELEMENTOR_BORDER_H

#include "Element.h"

namespace elementor {
    class Border : public Element, WithChild {
    public:
        Border *setColor(SkColor color);

        Border *setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        Border *setColor(uint8_t r, uint8_t g, uint8_t b);

        Border *setColor(std::string hex);

        SkColor getColor();

        Border *setWidth(float width);

        float getWidth();

        Border *setRadius(float radiusX, float radiusY);

        Border *setRadius(float radiusXY);

        float getRadiusX();

        float getRadiusY();

        Border *setChild(Element *child);

        RenderSize getSize(RenderBoundaries boundaries) override;

        void paintBackground(SkCanvas *canvas, RenderSize size);

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        float width = 0.0;
        float radiusX = 0.0;
        float radiusY = 0.0;
        SkColor color;
    };

    Border *border();
}


#endif //ELEMENTOR_BORDER_H

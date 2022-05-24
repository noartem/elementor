//
// Created by noartem on 27.04.2022.
//

#ifndef ELEMENTOR_BORDER_H
#define ELEMENTOR_BORDER_H

#include "Element.h"

namespace elementor {
    enum class BorderStyle {
        Solid,
        Dotted,
        Dashed,
    };

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

        Border *setStyle(BorderStyle style);

        BorderStyle getStyle();

        Border *setChild(Element *child);

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect);

        std::vector <RenderElement> getRenderChildren(ApplicationContext *ctx, Size size) override;

    private:
        float width = 0.0;
        float radiusX = 0.0;
        float radiusY = 0.0;
        SkColor color;
        BorderStyle style = BorderStyle::Solid;
    };

    Border *border();
}


#endif //ELEMENTOR_BORDER_H

//
// Created by noartem on 15.04.2022.
//

#ifndef ELEMENTOR_BACKGROUND_H
#define ELEMENTOR_BACKGROUND_H

#include "Element.h"

namespace elementor {
    class Background : public Element, WithChild {
    public:
        Background *setColor(SkColor color);

        Background *setColor(uint8_t r, uint8_t g, uint8_t b);

        Background *setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        Background *setColor(std::string hex);

        SkColor getColor();

        Background *setChild(Element *child);

        void paintBackground(ApplicationContext *ctx, SkCanvas *canvas, ElementRect rect) override;

        Size getSize(ApplicationContext *ctx, Boundaries boundaries) override;

        std::vector <RenderElement> getRenderChildren(ApplicationContext *ctx, Size size) override;

    private:
        SkColor color;
    };

    Background *background();
}


#endif //ELEMENTOR_BACKGROUND_H

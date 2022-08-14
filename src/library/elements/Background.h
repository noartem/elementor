//
// Created by noartem on 15.04.2022.
//

#ifndef ELEMENTOR_BACKGROUND_H
#define ELEMENTOR_BACKGROUND_H

#include "../Element.h"

namespace elementor::elements {
    class Background : public Element, public WithChild {
    public:
        Background *setColor(SkColor color);

        Background *setColor(uint8_t r, uint8_t g, uint8_t b);

        Background *setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        Background *setColor(std::string hex);

        SkColor getColor();

        Background *setChild(Element *child);

        void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) override;

        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

    private:
        SkColor color;
    };

    Background *background();
}


#endif //ELEMENTOR_BACKGROUND_H

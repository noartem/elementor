//
// Created by noartem on 15.04.2022.
//

#ifndef ELEMENTOR_BACKGROUND_H
#define ELEMENTOR_BACKGROUND_H

#include "Element.h"

namespace elementor {
    class Background : public Element, public WithChild {
    public:
        Background *setColor(SkColor color);

        Background *setColor(uint8_t r, uint8_t g, uint8_t b);

        Background *setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        Background *setColor(std::string hex);

        SkColor getColor();

        Background *setChild(Element *child);

        std::shared_ptr <ElementRenderer> render() override;

    private:
        SkColor color;
    };

    Background *background();

    class BackgroundRenderer : public ElementRenderer {
    public:
        BackgroundRenderer(ApplicationContext *context, SkColor color, Element *child);

        void paintBackground(SkCanvas *canvas, RenderSize size) override;

        std::vector <RenderElement> getChildren(RenderSize size) override;

    private:
        SkColor color;
        Element *child;
    };
}


#endif //ELEMENTOR_BACKGROUND_H

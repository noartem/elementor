//
// Created by noartem on 15.04.2022.
//

#ifndef ELEMENTOR_BACKGROUND_H
#define ELEMENTOR_BACKGROUND_H

#include "Element.h"

namespace elementor {
    class Background : public Element, public WithChild {
    public:
        Background() {};

        Background(Element *child);

        Background(SkColor color);

        Background(std::string color);

        Background(SkColor color, Element *child);

        Background(std::string color, Element *child);

        void setColor(SkColor color);

        void setColor(uint8_t r, uint8_t g, uint8_t b);

        void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        void setColor(std::string hex);

        std::shared_ptr <ElementRenderer> render() override;

    private:
        SkColor color;
    };

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

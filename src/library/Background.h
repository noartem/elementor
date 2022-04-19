//
// Created by noartem on 15.04.2022.
//

#ifndef ELEMENTOR_BACKGROUND_H
#define ELEMENTOR_BACKGROUND_H

#include "Element.h"

namespace elementor {
    class Background : public Element {
    public:
        SkColor color;
        Element *child;

        void setColor(uint8_t r, uint8_t g, uint8_t b);

        void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        void setColor(std::string hex);

        std::shared_ptr <ElementRenderer> render() override;
    };

    class BackgroundRenderer : public ElementRenderer {
    public:
        SkColor color;
        Element *child;

        void paintBackground(SkCanvas *canvas, RenderPosition start, RenderSize size) override;

        std::vector <RenderElement> getChildren(RenderSize size) override;
    };
}


#endif //ELEMENTOR_BACKGROUND_H

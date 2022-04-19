//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_ELEMENT_H
#define ELEMENTOR_ELEMENT_H

#include <include/core/SkCanvas.h>
#include <vector>

namespace elementor {
    class Element;
    class ElementRenderer;

    struct RenderPosition {
        int x;
        int y;
    };

    struct RenderSize {
        int width;
        int height;
    };

    struct RenderBoundaries {
        RenderSize min;
        RenderSize max;
    };

    struct RenderElement {
        RenderPosition position;
        RenderSize size;
        std::shared_ptr <ElementRenderer> renderer;
        Element *element;
    };

    class ElementRenderer {
    public:
        virtual RenderSize getSize(RenderBoundaries boundaries);

        virtual void paintBackground(SkCanvas *canvas, RenderPosition start, RenderSize size);

        virtual std::vector <RenderElement> getChildren(RenderSize size);
    };

    class Element {
    public:
        virtual std::shared_ptr <ElementRenderer> render();
    };
}

#endif //ELEMENTOR_ELEMENT_H

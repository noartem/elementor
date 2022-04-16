//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_ELEMENT_H
#define ELEMENTOR_ELEMENT_H

#include <include/core/SkCanvas.h>
#include <vector>

namespace elementor {
    class Element;

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

    struct RenderChild {
        RenderPosition position;
        RenderSize size;
        Element* element;
    };

    class ElementRenderer {
    public:
        virtual RenderSize getSize(RenderBoundaries boundaries);
    
        virtual void paintBackground(SkCanvas *canvas, RenderPosition start, RenderSize size);
    
        virtual std::vector <RenderChild> getChildren(RenderSize size);
    };

    class Element {
    public:
        virtual std::unique_ptr<ElementRenderer> render();
    };
}

#endif //ELEMENTOR_ELEMENT_H

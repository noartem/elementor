//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_ELEMENT_H
#define ELEMENTOR_ELEMENT_H

#include "ApplicationContext.h"

#include <include/core/SkCanvas.h>
#include <vector>

namespace elementor {
    class Element;

    class ElementRenderer;

    struct RenderElement {
        RenderPosition position;
        RenderSize size;
        std::shared_ptr <ElementRenderer> renderer;
        Element *element;
    };

    class ElementRenderer {
    public:
        ApplicationContext *context;

        virtual RenderSize getSize(RenderBoundaries boundaries);

        virtual void paintBackground(SkCanvas *canvas, RenderSize size);

        virtual std::vector <RenderElement> getChildren(RenderSize size);
    };

    class Element {
    public:
        ApplicationContext *context;
        virtual std::shared_ptr <ElementRenderer> render();
    };
}

#endif //ELEMENTOR_ELEMENT_H

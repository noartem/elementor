//
// Created by noartem on 02.01.2023.
//

#ifndef ELEMENTOR_COMPONENT_H
#define ELEMENTOR_COMPONENT_H

#include "Element.h"

namespace elementor::elements {
    class Component : public Element {
    public:
        Size getSize(ApplicationContext *ctx, Window *window, Boundaries boundaries) override;

        void paintBackground(ApplicationContext *ctx, Window *window, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getChildren(ApplicationContext *ctx, Window *window, Size size) override;

    protected:
        ApplicationContext *ctx;
        Window *window;
        ElementRect rect;
        Element *element;
    };
}


#endif //ELEMENTOR_COMPONENT_H

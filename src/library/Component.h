//
// Created by noartem on 02.01.2023.
//

#ifndef ELEMENTOR_COMPONENT_H
#define ELEMENTOR_COMPONENT_H

#include "Element.h"

namespace elementor::elements {
    class Component : public Element {
    public:
        Size getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) override;

        void paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) override;

        std::vector <RenderElement> getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) override;

    protected:
        std::shared_ptr<ApplicationContext> ctx;
        std::shared_ptr<Window> window;
        ElementRect rect;
        std::shared_ptr<Element> element;
    };
}


#endif //ELEMENTOR_COMPONENT_H

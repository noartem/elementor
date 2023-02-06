//
// Created by noartem on 02.01.2023.
//

#include "Component.h"

namespace elementor::elements {
    Size Component::getSize(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, Boundaries boundaries) {
        this->ctx = ctx;
        this->window = window;

        return this->element->getSize(ctx, window, boundaries);
    }

    void Component::paintBackground(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, SkCanvas *canvas, ElementRect rect) {
        this->ctx = ctx;
        this->window = window;
        this->rect = rect;
    }

    std::vector <RenderElement> Component::getChildren(std::shared_ptr<ApplicationContext> ctx, std::shared_ptr<Window> window, ElementRect rect) {
        this->ctx = ctx;
        this->window = window;

        RenderElement renderElement{this->element, {0, 0}, rect.size};
        return {renderElement};
    }
}

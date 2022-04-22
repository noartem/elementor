//
// Created by noartem on 13.04.2022.
//

#include "Application.h"
#include "Element.h"

namespace elementor {
    void Application::draw(SkCanvas *canvas, ApplicationContext context) {
        RenderElement rootElement;
        rootElement.position = {0, 0};
        rootElement.size = context.windowSize;
        rootElement.element = this->root;
        rootElement.element->context = &context;
        rootElement.renderer = this->root->render();
        this->drawElement(canvas, &rootElement);
    }

    void Application::drawElement(SkCanvas *canvas, RenderElement *element) {
        canvas->save();

        canvas->translate(element->position.x, element->position.y);
        element->renderer->paintBackground(canvas, element->size);

        for (RenderElement child: element->renderer->getChildren(element->size)) {
            this->drawElement(canvas, &child);
        }

        canvas->restore();
    }
}

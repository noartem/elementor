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
        this->drawElement(canvas, &rootElement, {0, 0});
    }

    void Application::drawElement(SkCanvas *canvas, RenderElement *element, RenderPosition parentPosition) {
        canvas->save();

        RenderPosition elementPosition = {element->position.x + parentPosition.x,
                                          element->position.y + parentPosition.y};
        element->renderer->paintBackground(canvas, elementPosition, element->size);

        for (RenderElement child: element->renderer->getChildren(element->size)) {
            this->drawElement(canvas, &child, elementPosition);
        }

        canvas->restore();
    }
}

//
// Created by noartem on 13.04.2022.
//

#include "Application.h"
#include "Element.h"

namespace elementor {
    void Application::draw(SkCanvas *canvas, RenderSize applicationSize) {
        std::unique_ptr<ElementRenderer> rootRenderer = this->root->render();

        RenderPosition rootPosition = {0, 0};
        rootRenderer->paintBackground(canvas, rootPosition, applicationSize);

        for (RenderChild child: rootRenderer->getChildren(applicationSize)) {
            std::unique_ptr<ElementRenderer> childRenderer = child.element->render();

            RenderPosition childPosition = {child.position.x + rootPosition.x, child.position.y + rootPosition.y};
            childRenderer->paintBackground(canvas, childPosition, child.size);

            for (RenderChild innerChild: childRenderer->getChildren(child.size)) {
                std::unique_ptr<ElementRenderer> innerChildRenderer = innerChild.element->render();

                RenderPosition innerChildPosition = {innerChild.position.x + childPosition.x, innerChild.position.y + childPosition.y};
                innerChildRenderer->paintBackground(canvas, innerChildPosition, innerChild.size);
            }
        }
    }
}

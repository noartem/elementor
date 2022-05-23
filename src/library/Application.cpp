//
// Created by noartem on 13.04.2022.
//

#include "Application.h"

namespace elementor {
    void Application::draw(SkCanvas *canvas, ApplicationContext context) {
        this->eventListeners.clear();

        RenderElement rootElement;
        rootElement.position = {0, 0};
        rootElement.size = context.windowSize;
        rootElement.element = this->root;
        rootElement.element->context = &context;

        ElementRect rootRect;
        rootRect.position = rootElement.position;
        rootRect.inParentPosition = rootElement.position;
        rootRect.size = rootElement.size;
        rootRect.visibleSize = rootElement.size;

        Rect rootBoundary;
        rootBoundary.position = rootElement.position;
        rootBoundary.size = rootElement.size;

        this->drawElement(canvas, &rootElement, rootRect, rootBoundary);
    }

    void Application::drawElement(SkCanvas *canvas, RenderElement *element, ElementRect rect, Rect boundary) {
        this->saveElementEventListeners(element->element);

        canvas->save();
        canvas->translate(element->position.x, element->position.y);

        ClipBehavior clipBehavior = element->element->getClipBehaviour();
        if (clipBehavior != ClipBehavior::None) {
            boundary = {rect.size, rect.position};
            canvas->clipRect(SkRect::MakeWH(boundary.size.width, boundary.size.height), SkClipOp::kIntersect, clipBehavior == ClipBehavior::Hard);
        }

        element->element->paintBackground(canvas, rect);

        for (RenderElement child: element->element->getRenderChildren(element->size)) {
            ElementRect childRect;
            childRect.position.x = rect.position.x + child.position.x;
            childRect.position.y = rect.position.y + child.position.y;
            childRect.visibleSize.width = std::min(std::max(boundary.size.width - std::max(childRect.position.x - boundary.position.x, 0), 0), child.size.width);
            childRect.visibleSize.height = std::min(std::max(boundary.size.height - std::max(childRect.position.y - boundary.position.y, 0), 0), child.size.height);
            childRect.size = child.size;
            childRect.inParentPosition = child.position;

            this->drawElement(canvas, &child, childRect, boundary);
        }

        canvas->restore();
    }

    void Application::saveElementEventListeners(Element *element) {
        for (std::string event : getElementEvents(element)) {
            this->eventListeners[event].push_back(element);
        }
    }

    void Application::dispatchEvent(Event *event) {
        if (this->eventListeners.count(event->getName())) {
            std::vector<Element *> listeners = this->eventListeners[event->getName()];
            for (int i = listeners.size() - 1; i >= 0; i--) {
                EventCallbackResponse callbackResponse = callElementEventHandler(listeners[i], event);
                if (callbackResponse == EventCallbackResponse::StopPropagation) {
                    break;
                }
            }
        }
    }
}

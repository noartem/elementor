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

        Rect rootRect;
        rootRect.position = rootElement.position;
        rootRect.size = rootElement.size;

        this->drawElement(canvas, &rootElement, rootRect, rootRect);
    }

    void Application::drawElement(SkCanvas *canvas, RenderElement *element, Rect rect, Rect boundary) {
        this->saveElementEventListeners(element->element);

        canvas->save();
        canvas->translate(element->position.x, element->position.y);

        ClipBehavior clipBehavior = element->element->getClipBehaviour();
        if (clipBehavior != ClipBehavior::None) {
            boundary = rect;
            canvas->clipRect(SkRect::MakeWH(boundary.size.width, boundary.size.height), SkClipOp::kIntersect, clipBehavior == ClipBehavior::Hard);
        }

        element->element->paintBackground(canvas, element->size, rect);

        for (RenderElement child: element->element->getRenderChildren(element->size)) {
            Rect childRect;
            childRect.position.x = rect.position.x + child.position.x;
            childRect.position.y = rect.position.y + child.position.y;
            childRect.size.width = std::min(std::max(boundary.size.width - std::max(childRect.position.x - boundary.position.x, 0), 0), child.size.width);
            childRect.size.height = std::min(std::max(boundary.size.height - std::max(childRect.position.y - boundary.position.y, 0), 0), child.size.height);

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
        if (this->eventListeners.contains(event->getName())) {
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

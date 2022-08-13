//
// Created by noartem on 13.04.2022.
//

#include "Application.h"

namespace elementor {
    void Application::draw(ApplicationContext *ctx, SkCanvas *canvas) {
        this->eventListeners.clear();

        RenderElement rootElement;
        rootElement.position = {0, 0};
        rootElement.size = ctx->window->size;
        rootElement.element = this->root;

        ElementRect rootRect;
        rootRect.position = {0, 0};
        rootRect.inParentPosition = {0, 0};
        rootRect.size = ctx->window->size;
        rootRect.visibleSize = ctx->window->size;

        Rect rootBoundary;
        rootBoundary.position = {0, 0};
        rootBoundary.size = ctx->window->size;

        this->drawElement(ctx, canvas, &rootElement, rootRect, rootBoundary);
    }

    void Application::drawElement(ApplicationContext *ctx, SkCanvas *canvas, RenderElement *element, ElementRect rect, Rect boundary) {
        this->saveElementEventListeners(element->element);

        canvas->save();
        canvas->translate(element->position.x, element->position.y);

        ClipBehavior clipBehavior = element->element->getClipBehaviour();
        if (clipBehavior != ClipBehavior::None) {
            boundary = {rect.size, rect.position};
            canvas->clipRect(SkRect::MakeWH(boundary.size.width, boundary.size.height), SkClipOp::kIntersect, clipBehavior == ClipBehavior::Hard);
        }

        element->element->paintBackground(ctx, canvas, rect);

#ifdef DEBUG
        SkPaint debugPaint;
        debugPaint.setColor(SK_ColorRED);
        debugPaint.setStrokeWidth(2);
        debugPaint.setStyle(SkPaint::kStroke_Style);
        debugPaint.setAntiAlias(true);

        SkRect debugRect = SkRect::MakeXYWH(0, 0, element->size.width, element->size.height);
        canvas->drawRect(debugRect, debugPaint);
#endif

        for (RenderElement child: element->element->getChildren(ctx, element->size)) {
            ElementRect childRect;
            childRect.position.x = rect.position.x + child.position.x;
            childRect.position.y = rect.position.y + child.position.y;
            childRect.visibleSize.width = std::min(std::max(boundary.size.width - std::max(childRect.position.x - boundary.position.x, ZERO), ZERO), child.size.width);
            childRect.visibleSize.height = std::min(std::max(boundary.size.height - std::max(childRect.position.y - boundary.position.y, ZERO), ZERO), child.size.height);
            childRect.size = child.size;
            childRect.inParentPosition = child.position;

            this->drawElement(ctx, canvas, &child, childRect, boundary);
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

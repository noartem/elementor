//
// Created by noartem on 13.04.2022.
//

#include "Application.h"

namespace elementor {
    ElementNode Application::makeNode(const RenderElement &element, const ElementRect &rect, const Rect &rootBoundary) {
        Rect boundary = rootBoundary;
        if (element.element->getClipBehaviour() != ClipBehavior::None) {
            boundary = {rect.size, rect.position};
        }

        std::vector <ElementNode> children;
        for (const RenderElement &child: element.element->getChildren(ctx, window, rect)) {
            ElementRect childRect{};
            childRect.position.x = rect.position.x + child.position.x;
            childRect.position.y = rect.position.y + child.position.y;
            childRect.visibleSize.width = std::min(
                    std::max(boundary.size.width - std::max(childRect.position.x - boundary.position.x, ZERO), ZERO),
                    child.size.width);
            childRect.visibleSize.height = std::min(
                    std::max(boundary.size.height - std::max(childRect.position.y - boundary.position.y, ZERO), ZERO),
                    child.size.height);
            childRect.size = child.size;
            childRect.inParentPosition = child.position;

            children.push_back(this->makeNode(child, childRect, boundary));
        }

        return ElementNode{
                .element =  element.element,
                .rect =  rect,
                .children =  children,
        };
    }

    ElementNode Application::makeRootNode() {
        RenderElement rootElement{};
        rootElement.position = {0, 0};
        rootElement.size = window->getSize();
        rootElement.element = window->getRoot();

        ElementRect rootRect{};
        rootRect.position = {0, 0};
        rootRect.inParentPosition = {0, 0};
        rootRect.size = window->getSize();
        rootRect.visibleSize = window->getSize();

        Rect rootBoundary{};
        rootBoundary.position = {0, 0};
        rootBoundary.size = window->getSize();

        return this->makeNode(rootElement, rootRect, rootBoundary);
    }

    void Application::saveElementEventListeners(const std::shared_ptr <Element> &element) {
        for (const std::string &event: getElementEvents(element)) {
            this->eventListeners[event].push_back(element);
        }
    }

    void Application::drawNode(const ElementNode &node, SkCanvas *canvas) {
        this->saveElementEventListeners(node.element);

        canvas->save();
        canvas->translate(node.rect.inParentPosition.x, node.rect.inParentPosition.y);

        ClipBehavior clipBehavior = node.element->getClipBehaviour();
        if (clipBehavior != ClipBehavior::None) {
            canvas->clipRect(SkRect::MakeWH(node.rect.visibleSize.width, node.rect.visibleSize.height),
                             SkClipOp::kIntersect, clipBehavior == ClipBehavior::Hard);
        }

        node.element->paintBackground(ctx, window, canvas, node.rect);

#ifdef DEBUG
        SkPaint debugPaint;
        debugPaint.setColor(SK_ColorRED);
        debugPaint.setStrokeWidth(2);
        debugPaint.setStyle(SkPaint::kStroke_Style);
        debugPaint.setAntiAlias(true);

        SkRect debugRect = SkRect::MakeWH(node.rect.visibleSize.width, node.rect.visibleSize.height);
        canvas->drawRect(debugRect, debugPaint);
#endif

        for (const ElementNode &child: node.children) {
            this->drawNode(child, canvas);
        }

        canvas->restore();
    }

    void Application::draw(SkCanvas *canvas) {
        this->eventListeners.clear();

        this->rootNode = this->makeRootNode();
        this->drawNode(this->rootNode, canvas);
    }

    void Application::dispatchEvent(const std::shared_ptr <Event> &event) {
        if (this->eventListeners.count(event->getName())) {
            std::vector <std::shared_ptr<Element>> listeners = this->eventListeners[event->getName()];
            for (int i = listeners.size() - 1; i >= 0; i--) {
                EventCallbackResponse callbackResponse = callElementEventHandler(listeners[i], event);
                if (callbackResponse == EventCallbackResponse::StopPropagation) {
                    break;
                }
            }
        }
    }
}

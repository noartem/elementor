//
// Created by noartem on 13.04.2022.
//

#include "Application.h"

namespace elementor {
    std::shared_ptr <ElementNode> Application::makeNode(const RenderElement &element, const ElementRect &rect, const Rect &rootBoundary) {
        auto node = std::make_shared<ElementNode>();

        node->element = element.element;
        node->rect = rect;

        Rect boundary = rootBoundary;
        if (element.element->getClipBehaviour() != ClipBehavior::None) {
            boundary = {rect.size, rect.position};
        }

        for (const RenderElement &child: element.element->getChildren(ctx, window, rect)) {
            ElementRect childRect{};
            childRect.position.x = rect.position.x + child.position.x;
            childRect.position.y = rect.position.y + child.position.y;
            childRect.visibleSize.width = std::min(
                    std::max(boundary.size.width - std::max(childRect.position.x - boundary.position.x, ZERO), ZERO),
                    child.size.width
            );
            childRect.visibleSize.height = std::min(
                    std::max(boundary.size.height - std::max(childRect.position.y - boundary.position.y, ZERO), ZERO),
                    child.size.height
            );
            childRect.size = child.size;
            childRect.inParentPosition = child.position;

            auto childNode = this->makeNode(child, childRect, boundary);
            childNode->parent = node;
            node->children.push_back(childNode);
        }

        return node;
    }

    std::shared_ptr <ElementNode> Application::makeRootNode() {
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

    void Application::saveNodeEventListeners(const std::shared_ptr <ElementNode> &node) {
        for (const std::string &event: getElementEvents(node->element)) {
            this->eventListeners[event].push_back(node);
        }
    }

    void Application::drawNode(const std::shared_ptr <ElementNode> &node, SkCanvas *canvas) {
        this->saveNodeEventListeners(node);

        canvas->save();
        canvas->translate(node->rect.inParentPosition.x, node->rect.inParentPosition.y);

        ClipBehavior clipBehavior = node->element->getClipBehaviour();
        if (clipBehavior != ClipBehavior::None) {
            canvas->clipRect(SkRect::MakeWH(node->rect.visibleSize.width, node->rect.visibleSize.height),
                             SkClipOp::kIntersect, clipBehavior == ClipBehavior::Hard);
        }

        node->element->paintBackground(ctx, window, canvas, node->rect);

#ifdef DEBUG
        SkPaint debugPaint;
        debugPaint.setColor(SK_ColorRED);
        debugPaint.setStrokeWidth(2);
        debugPaint.setStyle(SkPaint::kStroke_Style);
        debugPaint.setAntiAlias(true);

        SkRect debugRect = SkRect::MakeWH(node.rect.visibleSize.width, node.rect.visibleSize.height);
        canvas->drawRect(debugRect, debugPaint);
#endif

        for (const auto &child: node->children) {
            this->drawNode(child, canvas);
        }

        canvas->restore();
    }

    void Application::draw(SkCanvas *canvas) {
        this->eventListeners.clear();

        this->rootNode = this->makeRootNode();
        this->drawNode(this->rootNode, canvas);
    }

    void Application::setHoveredElements(const std::vector <std::shared_ptr<ElementNode>> &newValue) {
        auto oldValue = this->hoveredElements;
        this->hoveredElements = newValue;

        if (newValue.size() == oldValue.size()) {
            bool equals = true;
            for (int i = 0; i < newValue.size(); i++) {
                if (newValue[i]->element != oldValue[i]->element) {
                    equals = false;
                    break;
                }
            }
            if (equals) {
                return;
            }
        }

        for (const auto &node: oldValue) {
            if (std::find_if(newValue.begin(), newValue.end(), [node](const std::shared_ptr <ElementNode> &newNode) { return node->element == newNode->element; }) == newValue.end()) {
                callElementEventHandler(node->element, std::make_shared<EventHover>(false));
            }
        }

        for (const auto &node: newValue) {
            if (std::find_if(oldValue.begin(), oldValue.end(), [node](const std::shared_ptr <ElementNode> &oldNode) { return node->element == oldNode->element; }) == oldValue.end()) {
                callElementEventHandler(node->element, std::make_shared<EventHover>(true));
            }
        }
    }

    void Application::onMouseMove(const std::shared_ptr <EventMouseMove> &event) {
        auto hoverableNodes = this->eventListeners[EVENT_HOVER];
        for (int i = hoverableNodes.size() - 1; i >= 0; i--) {
            auto node = hoverableNodes[i];

            if (node->rect.visibleContains(event->x, event->y)) {
                std::vector <std::shared_ptr<ElementNode>> nodes;
                std::shared_ptr <ElementNode> currentNode = node;
                while (currentNode != nullptr) {
                    if (!currentNode->rect.visibleContains(event->x, event->y)) {
                        break;
                    }

                    if (dynamic_cast<WithOnHover *>(currentNode->element.get()) != nullptr) {
                        nodes.push_back(currentNode);
                    }

                    if (currentNode->parent.expired()) {
                        currentNode = nullptr;
                    } else {
                        currentNode = currentNode->parent.lock();
                    }
                }

                this->setHoveredElements(nodes);
                return;
            }
        }

        this->setHoveredElements({});
    }

    void Application::dispatchEvent(const std::shared_ptr <Event> &event) {
        auto eventMouseMove = std::dynamic_pointer_cast<EventMouseMove>(event);
        if (eventMouseMove != nullptr) {
            this->onMouseMove(eventMouseMove);
        }

        if (this->eventListeners.count(event->getName())) {
            auto nodes = this->eventListeners[event->getName()];
            for (int i = nodes.size() - 1; i >= 0; i--) {
                auto node = nodes[i];
                auto element = node->element;
                EventCallbackResponse callbackResponse = callElementEventHandler(element, event);
                if (callbackResponse == EventCallbackResponse::StopPropagation) {
                    break;
                }
            }
        }
    }
}

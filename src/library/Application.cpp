//
// Created by noartem on 13.04.2022.
//

#include "Application.h"

#include <iostream>

namespace elementor {
    std::shared_ptr <ElementNode> Application::makeNode(const RenderElement &element,
                                                        const ElementRect &rect, const Rect &rootBoundary) {
        auto node = std::make_shared<ElementNode>();

        node->element = element.element;
        node->rect = rect;

        Rect boundary = rootBoundary;
        if (element.element->getClipBehaviour() != ClipBehavior::None) {
            boundary.position.x = std::max(rootBoundary.position.x, rect.position.x);
            boundary.position.y = std::max(rootBoundary.position.y, rect.position.y);
            boundary.size.width = std::max(
                    std::min(rootBoundary.position.x + rootBoundary.size.width, rect.position.x + rect.size.width) -
                    boundary.position.x, ZERO);
            boundary.size.height = std::max(
                    std::min(rootBoundary.position.y + rootBoundary.size.height, rect.position.y + rect.size.height) -
                    boundary.position.y, ZERO);
        }

        for (const RenderElement &child: element.element->getChildren(ctx, window, rect)) {
            ElementRect childRect{};

            childRect.position.x = rect.position.x + child.position.x;
            childRect.position.y = rect.position.y + child.position.y;
            childRect.size = child.size;
            childRect.inParentPosition = child.position;

            childRect.visiblePosition.x = std::max(childRect.position.x, boundary.position.x);
            childRect.visiblePosition.y = std::max(childRect.position.y, boundary.position.y);
            childRect.visibleSize.width = std::max(
                    std::min(boundary.position.x + boundary.size.width, childRect.position.x + childRect.size.width) -
                    childRect.visiblePosition.x, ZERO);
            childRect.visibleSize.height = std::max(
                    std::min(boundary.position.y + boundary.size.height, childRect.position.y + childRect.size.height) -
                    childRect.visiblePosition.y, ZERO);

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
        rootRect.visiblePosition = {0, 0};
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

        for (const auto &child: node->children) {
            this->saveNodeEventListeners(child);
        }
    }

    void Application::drawNode(const std::shared_ptr <ElementNode> &node, SkCanvas *canvas) {
        canvas->save();
        canvas->translate(node->rect.inParentPosition.x, node->rect.inParentPosition.y);

        ClipBehavior clipBehavior = node->element->getClipBehaviour();
        if (clipBehavior != ClipBehavior::None) {
            SkRect rect = SkRect::MakeXYWH(
                    node->rect.visiblePosition.x - node->rect.position.x,
                    node->rect.visiblePosition.y - node->rect.position.y,
                    node->rect.visibleSize.width,
                    node->rect.visibleSize.height
            );
            canvas->clipRect(rect, SkClipOp::kIntersect, clipBehavior == ClipBehavior::Hard);
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
            if (std::find_if(newValue.begin(), newValue.end(),
                             [node](const std::shared_ptr <ElementNode> &newNode) {
                                 return node->element == newNode->element;
                             })
                == newValue.end()) {
                callElementEventHandler(node->element, std::make_shared<EventHover>(false));
            }
        }

        for (const auto &node: newValue) {
            if (std::find_if(oldValue.begin(), oldValue.end(),
                             [node](const std::shared_ptr <ElementNode> &oldNode) {
                                 return node->element == oldNode->element;
                             })
                == oldValue.end()) {
                callElementEventHandler(node->element, std::make_shared<EventHover>(true));
            }
        }
    }

    template<typename T>
    std::optional <T> findLast(std::vector <T> items, std::function<bool(T item)> iter) {
        for (int i = items.size() - 1; i >= 0; i--) {
            T item = items[i];
            if (iter(item)) {
                return item;
            }
        }

        return std::nullopt;
    }

    void Application::updateHovered() {
        if (!this->window->getFocused()) {
            this->setHoveredElements({});
            return;
        }

        auto cursorPosition = this->window->getCursor()->getPosition();

        auto hoveredNode = findLast<std::shared_ptr < ElementNode>>
        (this->eventListeners[EVENT_HOVER],
                [cursorPosition](std::shared_ptr <ElementNode> node) {
                    return node->rect.visibleContains(cursorPosition);
                });
        if (hoveredNode == std::nullopt) {
            this->setHoveredElements({});
            return;
        }

        std::vector <std::shared_ptr<ElementNode>> hoveredNodes;
        std::shared_ptr <ElementNode> currentNode = hoveredNode.value();
        while (currentNode != nullptr) {
            if (!currentNode->rect.visibleContains(cursorPosition)) {
                break;
            }

            if (dynamic_cast<WithOnHover *>(currentNode->element.get()) != nullptr) {
                hoveredNodes.push_back(currentNode);
            }

            if (currentNode->parent.expired()) {
                currentNode = nullptr;
            } else {
                currentNode = currentNode->parent.lock();
            }
        }

        this->setHoveredElements(hoveredNodes);
    }

    void Application::draw(SkCanvas *canvas) {
        this->rootNode = this->makeRootNode();

        this->eventListeners.clear();
        this->saveNodeEventListeners(this->rootNode);

        this->updateHovered();
        this->dispatchPendingEvents();

        this->drawNode(this->rootNode, canvas);
    }

    void Application::dispatchPendingEvents() {
        if (this->pendingEvents.size() == 0) {
            return;
        }

        for (const auto &event: this->pendingEvents) {
            if (this->eventListeners.count(event->getName()) == 0) {
                continue;
            }

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

        this->pendingEvents = {};
    }

    void Application::dispatchEvent(const std::shared_ptr <Event> &event) {
        this->pendingEvents.push_back(event);
    }
}

F//
// Created by admin on 12.01.2024.
//

#include "ElementTree.h"

#include <memory>
#include <vector>

#include "Render.h"
#include "WindowContext.h"
#include "Element.h"

namespace elementor {
	ElementTreeNode::ElementTreeNode(
		const std::shared_ptr<Element>& element,
		const elementor::ElementRect& rect,
		const std::shared_ptr<ElementTreeNode>& parent
	)
		: element(element), rect(rect), parent(parent), children({}) {
		const auto& elementWithEventsHandlers = std::dynamic_pointer_cast<WithEventsHandlers>(element);
		if (elementWithEventsHandlers) {
			for (const auto& eventHandler: elementWithEventsHandlers->getEventsHandlers()) {
				eventsHandlers[eventHandler->getName()].push_back(eventHandler);
			}
		}

		const auto& eventWithGlobalEventsHandlers = std::dynamic_pointer_cast<WithGlobalEventsHandlers>(element);
		if (eventWithGlobalEventsHandlers) {
			globalEventsHandlers = eventWithGlobalEventsHandlers->getGlobalEventsHandlers();
		}
	}

	std::shared_ptr<ElementTreeNode> ElementTreeNode::Make(
		const std::shared_ptr<Element>& element,
		const ElementRect& rect,
		const std::shared_ptr<ElementTreeNode>& parent,
		const Rect& parentBoundary
	) {
		auto node = std::make_shared<ElementTreeNode>(element, rect, parent);

		Rect boundary = element->getClipBehaviour() == ClipBehavior::None
						? parentBoundary
						: unionOfRects(parentBoundary, rect);

		for (const auto& childElementWithRect: element->getChildren(rect)) {
			auto childElement = std::get<0>(childElementWithRect);
			auto childRect = std::get<1>(childElementWithRect);

			ElementRect childElementRect{};

			childElementRect.size = childRect.size;
			childElementRect.position.x = rect.position.x + childRect.position.x;
			childElementRect.position.y = rect.position.y + childRect.position.y;
			childElementRect.inParentPosition = childRect.position;

			auto childVisibleRect = unionOfRects(boundary, childElementRect);
			childElementRect.visibleSize = childVisibleRect.size;
			childElementRect.visiblePosition = childVisibleRect.position;

			auto childNode = ElementTreeNode::Make(childElement, childElementRect, node, boundary);
			node->addChild(childNode);
		}

		return node;
	}

	std::shared_ptr<ElementTreeNode> ElementTreeNode::MakeRoot(
		const std::shared_ptr<Element>& element,
		const std::shared_ptr<WindowContext>& windowCtx
	) {
		Size windowSize = windowCtx->getSize();

		ElementRect rootRect{};
		rootRect.position = { 0, 0 };
		rootRect.inParentPosition = { 0, 0 };
		rootRect.size = element->getSize({ .min = windowSize, .max = windowSize });
		rootRect.visiblePosition = { 0, 0 };
		rootRect.visibleSize = windowCtx->getSize();

		Rect rootBoundary{};
		rootBoundary.position = { 0, 0 };
		rootBoundary.size = windowCtx->getSize();

		return ElementTreeNode::Make(element, rootRect, nullptr, rootBoundary);
	}

	std::shared_ptr<ElementTreeNode> ElementTreeNode::findElementNode(const std::shared_ptr<Element>& targetElement) {
		if (element == targetElement) {
			return shared_from_this();
		}

		for (const auto& childNode: children) {
			auto foundNode = childNode->findElementNode(targetElement);
			if (foundNode != nullptr) {
				return foundNode;
			}
		}

		return nullptr;
	}

	EventCallbackResponse ElementTreeNode::onEvent(const std::shared_ptr<Event>& event) const {
		for (const auto& eventHandler: getEventHandlers(event->getName())) {
			auto response = eventHandler->onEvent(event);
			if (response != EventCallbackResponse::None) {
				return response;
			}
		}

		return EventCallbackResponse::None;
	}

	EventCallbackResponse ElementTreeNode::bubbleEvent(const std::shared_ptr<Event>& event) const {
		auto currentNode = shared_from_this();

		while (currentNode != nullptr) {
			auto response = currentNode->onEvent(event);
			if (response != EventCallbackResponse::None) {
				return response;
			}

			currentNode = currentNode->getParent();
		}

		return EventCallbackResponse::None;
	}
}
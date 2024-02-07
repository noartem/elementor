//
// Created by noartem on 13.04.2022.
//

#include <ranges>
#include "Application.h"
#include "utils.h"

namespace elementor::application {
	void Application::draw(SkCanvas* canvas) {
		rootNode = ElementTreeNode::MakeRoot(root, windowCtx);

		updateHoveredNode();
		updateFocusableNodes();
		updateGlobalEventsHandlers();
		dispatchPendingEvents();

		drawNode(rootNode, canvas);
	}

	void Application::drawNode(const std::shared_ptr<ElementTreeNode>& node, SkCanvas* canvas) {
		auto element = node->getElement();
		auto rect = node->getRect();
		auto children = node->getChildren();

		canvas->save();
		canvas->translate(rect.inParentPosition.x, rect.inParentPosition.y);

		ClipBehavior clipBehavior = element->getClipBehaviour();
		if (clipBehavior != ClipBehavior::None) {
			SkRect skRect = SkRect::MakeXYWH(
				rect.visiblePosition.x - rect.position.x,
				rect.visiblePosition.y - rect.position.y,
				rect.visibleSize.width,
				rect.visibleSize.height
			);
			canvas->clipRect(skRect, SkClipOp::kIntersect, clipBehavior == ClipBehavior::AntiAlias);
		}

		element->paintBackground(canvas, rect);

#ifdef DEBUG
		SkPaint debugSkPaint;
		debugSkPaint.setColor(SK_ColorRED);
		debugSkPaint.setStrokeWidth(2);
		debugSkPaint.setStyle(SkPaint::kStroke_Style);
		debugSkPaint.setAntiAlias(true);

		SkRect debugSkRect = SkRect::MakeWH(rect.visibleSize.width, rect.visibleSize.height);
		canvas->drawRect(debugSkRect, debugSkPaint);
#endif

		for (const auto& child: children) {
			drawNode(child, canvas);
		}

		canvas->restore();
	}

	bool isCursorCausedEvent(const std::shared_ptr<Event>& event) {
		return event->getName() == "mouse-button"
			|| event->getName() == "mouse-move"
			|| event->getName() == "scroll";
	}

	bool isGoToNextFocusableEvent(const std::shared_ptr<Event>& event) {
		auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
		return keyboardEvent != nullptr
			&& (keyboardEvent->action == KeyAction::Press || keyboardEvent->action == KeyAction::Repeat)
			&& keyboardEvent->mod != KeyMod::Shift
			&& keyboardEvent->key == KeyboardKey::Tab;
	}

	bool isGoToPreviousFocusableEvent(const std::shared_ptr<Event>& event) {
		auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
		return keyboardEvent != nullptr
			&& (keyboardEvent->action == KeyAction::Press || keyboardEvent->action == KeyAction::Repeat)
			&& keyboardEvent->mod == KeyMod::Shift
			&& keyboardEvent->key == KeyboardKey::Tab;
	}

	bool isFocusRelatedEvent(const std::shared_ptr<Event>& event) {
		return event->getName() == "keyboard"
			|| event->getName() == "char";
	}

	void Application::dispatchPendingEvents() {
		auto lastPendingEvents = pendingEvents;
		pendingEvents = {};

		for (const auto& event: lastPendingEvents) {
			if (hoveredNode && isCursorCausedEvent(event)) {
				auto bubbleEventResponse = hoveredNode->bubbleEvent(event);
				if (bubbleEventResponse == EventCallbackResponse::StopPropagation) {
					continue;
				}
			}

			if (focusedNode && isFocusRelatedEvent(event)) {
				auto bubbleEventResponse = focusedNode->bubbleEvent(event);
				if (bubbleEventResponse == EventCallbackResponse::StopPropagation) {
					continue;
				}
			}

			if (isGoToNextFocusableEvent(event)) {
				focusNextNode();
			} else if (isGoToPreviousFocusableEvent(event)) {
				focusPreviousNode();
			}

			auto eventListeners = eventsHandlers[event->getName()];
			for (const auto& eventHandler: eventsHandlers[event->getName()]) {
				if (eventHandler != nullptr) {
					continue;
				}

				auto eventHandlerResponse = eventHandler->onEvent(event);
				if (eventHandlerResponse != EventCallbackResponse::None) {
					break;
				}
			}
		}
	}

	std::shared_ptr<ElementTreeNode> Application::getHoveredNodeOrChild(
		const std::shared_ptr<ElementTreeNode>& node,
		const elementor::Position& cursorPosition
	) const {
		for (const auto& childNode: node->getChildren() | std::views::reverse) {
			if (childNode->getRect().contains(cursorPosition)) {
				return getHoveredNodeOrChild(childNode, cursorPosition);
			}
		}

		return node;
	}

	void Application::setHoveredNode(const std::shared_ptr<ElementTreeNode>& newHoveredNode) {
		if (hoveredNode && newHoveredNode && hoveredNode->getElement() == newHoveredNode->getElement()) {
			return;
		}

		if (hoveredNode) {
			auto hoverLeaveEvent = std::make_shared<HoverEvent>(false);
			hoveredNode->bubbleEvent(hoverLeaveEvent);

			hoveredNode = nullptr;
		}

		if (newHoveredNode) {
			auto hoverEnterEvent = std::make_shared<HoverEvent>(true);
			newHoveredNode->bubbleEvent(hoverEnterEvent);

			hoveredNode = newHoveredNode;
		}
	}

	void Application::updateHoveredNode() {
		auto cursorPosition = windowCtx->getCursor()->getPosition();
		if (cursorPosition.x == -1 && cursorPosition.y == -1) {
			setHoveredNode(nullptr);
			return;
		}

		const auto& newHoveredNode = getHoveredNodeOrChild(rootNode, cursorPosition);
		setHoveredNode(newHoveredNode);
	}

	void Application::pushTreeFocusableNodes(const std::shared_ptr<ElementTreeNode>& node) {
		auto nodeElementFocusable = std::dynamic_pointer_cast<elements::Focusable>(node->getElement());
		if (nodeElementFocusable != nullptr && nodeElementFocusable->isFocusAllowed()) {
			focusableNodes.push_back(node);
		}

		for (const auto& child: node->getChildren()) {
			pushTreeFocusableNodes(child);
		}
	}

	void Application::setFocusedNode(const std::shared_ptr<ElementTreeNode>& newFocusedNode) {
		if (newFocusedNode && focusedNode && newFocusedNode->getElement() == focusedNode->getElement()) {
			return;
		}

		if (focusedNode) {
			auto blurEvent = std::make_shared<FocusEvent>(false);
			focusedNode->onEvent(blurEvent);

			auto focusOutEvent = std::make_shared<FocusOutEvent>();
			focusedNode->bubbleEvent(focusOutEvent);

			focusedNode = nullptr;
		}

		if (newFocusedNode) {
			auto focusEvent = std::make_shared<FocusEvent>(true);
			newFocusedNode->onEvent(focusEvent);

			auto focusInEvent = std::make_shared<FocusInEvent>();
			newFocusedNode->bubbleEvent(focusInEvent);

			focusedNode = newFocusedNode;
		}
	}

	void Application::clearFocusedNodeIfRemoved() {
		if (focusedNode == nullptr) {
			return;
		}

		for (const auto& node: focusableNodes) {
			if (node->getElement() == focusedNode->getElement()) {
				return;
			}
		}

		setFocusedNode(nullptr);
	}

	bool isFocusableNodePendingBlur(const std::shared_ptr<ElementTreeNode>& node) {
		auto nodeElementFocusable = std::dynamic_pointer_cast<elements::Focusable>(node->getElement());
		if (nodeElementFocusable == nullptr) {
			return false;
		}

		return nodeElementFocusable->isPendingBlur();
	}

	bool isFocusableNodePendingFocus(const std::shared_ptr<ElementTreeNode>& node) {
		auto nodeElementFocusable = std::dynamic_pointer_cast<elements::Focusable>(node->getElement());
		if (nodeElementFocusable == nullptr) {
			return false;
		}

		return nodeElementFocusable->isPendingFocus();
	}

	void Application::clearFocusedNodeIfPendingBlur() {
		if (focusedNode && isFocusableNodePendingBlur(focusedNode)) {
			setFocusedNode(nullptr);
		}
	}

	void Application::updateFocusableNodes() {
		focusableNodes.clear();

		pushTreeFocusableNodes(rootNode);
		clearFocusedNodeIfRemoved();
		clearFocusedNodeIfPendingBlur();

		for (const auto& focusableNode: focusableNodes) {
			if (isFocusableNodePendingFocus(focusableNode)) {
				setFocusedNode(focusableNode);
				break;
			}
		}
	}

	int Application::getFocusedNodeIndex() {
		if (focusedNode == nullptr) {
			return -1;
		}

		for (int i = 0; i < focusableNodes.size(); i++) {
			if (focusableNodes[i]->getElement() == focusedNode->getElement()) {
				return i;
			}
		}

		return -1;
	}

	void Application::focusIthNode(int i) {
		if (focusableNodes.empty()) {
			return;
		}

		i = ring(i, focusableNodes.size());
		i = clamp(i, 0, focusableNodes.size() - 1);

		setFocusedNode(focusableNodes[i]);
	}

	void Application::focusNextNode() {
		auto i = getFocusedNodeIndex();
		focusIthNode(i == -1 ? 0 : (i + 1));
	}

	void Application::focusPreviousNode() {
		auto i = getFocusedNodeIndex();
		focusIthNode(i == -1 ? 0 : (i - 1));
	}

	void Application::pushTreeGlobalEventsHandlers(const std::shared_ptr<ElementTreeNode>& node) {
		for (const auto& eventHandler: node->getGlobalEventsHandlers()) {
			eventsHandlers[eventHandler->getName()].push_back(eventHandler);
		}

		for (const auto& child: node->getChildren()) {
			pushTreeGlobalEventsHandlers(child);
		}
	}

	void Application::updateGlobalEventsHandlers() {
		eventsHandlers.clear();
		pushTreeGlobalEventsHandlers(rootNode);
	}
}

//
// Created by noartem on 13.04.2022.
//

#include "Application.h"

#include <memory>
#include <ranges>

#include <include/core/SkCanvas.h>

#include "Element.h"
#include "ElementTree.h"
#include "Event.h"

#include "debug.h"

namespace elementor {
	template<typename T, typename... U>
	size_t getAddress(std::function<T(U...)> f) {
		typedef T(fnType)(U...);
		auto** fnPointer = f.template target<fnType*>();
		return (size_t)*fnPointer;
	}

	void Application::draw(SkCanvas* canvas) {
		rootNode = makeRootNode(root, windowCtx);
		drawNode(rootNode, canvas);

		platformCtx->requestNextFrame([this]() {
			updateHoveredNode();
			updateFocusableElements();
			dispatchPendingEvents();
		});
	}

	void Application::drawNode(const std::shared_ptr<ElementTreeNode>& node, SkCanvas* canvas) {
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

		node->element->paintBackground(canvas, node->rect);

#ifdef DEBUG
		SkPaint debugPaint;
		debugPaint.setColor(SK_ColorRED);
		debugPaint.setStrokeWidth(2);
		debugPaint.setStyle(SkPaint::kStroke_Style);
		debugPaint.setAntiAlias(true);

		SkRect debugRect = SkRect::MakeWH(node->rect.visibleSize.width, node->rect.visibleSize.height);
		canvas->drawRect(debugRect, debugPaint);
#endif

		for (const auto& child: node->children) {
			drawNode(child, canvas);
		}

		canvas->restore();
	}

	EventCallbackResponse callElementEventHandler(
		const std::shared_ptr<Element>& element,
		const std::shared_ptr<Event>& event
	) {
		const auto& elementEventHandler = std::dynamic_pointer_cast<WithEvents>(element);
		if (elementEventHandler == nullptr) {
			return EventCallbackResponse::None;
		}

		return elementEventHandler->onEvent(event);
	}

	EventCallbackResponse Application::bubbleEvent(
		const std::shared_ptr<ElementTreeNode>& elementNode,
		const std::shared_ptr<Event>& event
	) const {
		auto currentNode = elementNode;

		while (currentNode != nullptr) {
			auto elementResponse = callElementEventHandler(currentNode->element, event);
			if (elementResponse == EventCallbackResponse::StopPropagation) {
				return EventCallbackResponse::StopPropagation;
			}

			currentNode = currentNode->parent;
		}

		return EventCallbackResponse::None;
	}

	bool isCursorCausedEvent(const std::shared_ptr<Event>& event) {
		return event->getName() == "mouse-button"
			|| event->getName() == "mouse-move"
			|| event->getName() == "scroll";
	}

	bool isGoToNextFocusableEvent(const std::shared_ptr<Event>& event) {
		auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
		return keyboardEvent != nullptr
			&& keyboardEvent->action == KeyAction::Release
			&& keyboardEvent->mod != KeyMod::Shift
			&& keyboardEvent->key == KeyboardKey::Tab;
	}

	bool isGoToPreviousFocusableEvent(const std::shared_ptr<Event>& event) {
		auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
		return keyboardEvent != nullptr
			&& keyboardEvent->action == KeyAction::Release
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
				auto bubbleEventResponse = bubbleEvent(hoveredNode, event);
				if (bubbleEventResponse == EventCallbackResponse::StopPropagation) {
					continue;
				}
			} else if (focusedElement && isFocusRelatedEvent(event)) {
				auto focusedElementNode = getFocusedElementNode();
				auto bubbleEventResponse = bubbleEvent(focusedElementNode, event);
				if (bubbleEventResponse == EventCallbackResponse::StopPropagation) {
					continue;
				}
			} else if (isGoToNextFocusableEvent(event)) {
				focusNextFocusableElement();
			} else if (isGoToPreviousFocusableEvent(event)) {
				focusPreviousFocusableElement();
			}

			auto eventListeners = eventsListeners[event->getName()];
			for (const auto& listener: eventListeners) {
				if (listener == nullptr) {
					continue;
				}

				listener(event);
			}
		}
	}

	int Application::addEventListener(
		const std::string_view& eventName,
		const std::function<void(const std::shared_ptr<Event>&)>& eventListener
	) {
		for (int i = 0; i < eventsListeners[eventName].size(); i++) {
			if (eventsListeners[eventName][i] == nullptr) {
				eventsListeners[eventName][i] = eventListener;
				return i;
			}
		}

		eventsListeners[eventName].push_back(eventListener);
		return (int)eventsListeners[eventName].size() - 1;
	}

	void Application::removeEventListener(const std::string_view& eventName, int eventListenerIndex) {
		if (eventListenerIndex < 0 || eventListenerIndex >= eventsListeners[eventName].size()) {
			return;
		}

		eventsListeners[eventName][eventListenerIndex] = nullptr;
	}

	std::shared_ptr<ElementTreeNode> Application::getHoveredNodeOrChild(
		const std::shared_ptr<ElementTreeNode>& node,
		const elementor::Position& cursorPosition
	) const {
		for (const auto& childNode: node->children | std::views::reverse) {
			if (childNode->rect.contains(cursorPosition)) {
				return getHoveredNodeOrChild(childNode, cursorPosition);
			}
		}

		return node;
	}

	void Application::setHoveredNode(const std::shared_ptr<ElementTreeNode>& newHoveredNode) {
		if (hoveredNode && newHoveredNode && hoveredNode->element == newHoveredNode->element) {
			return;
		}

		if (hoveredNode) {
			auto hoverLeaveEvent = std::make_shared<HoverEvent>(false);
			bubbleEvent(hoveredNode, hoverLeaveEvent);

			hoveredNode = nullptr;
		}

		if (newHoveredNode) {
			auto hoverEnterEvent = std::make_shared<HoverEvent>(true);
			bubbleEvent(newHoveredNode, hoverEnterEvent);

			hoveredNode = newHoveredNode;
		}
	}

	void Application::updateHoveredNode() {
		auto cursorPosition = windowCtx->getCursor()->getPosition();
		const auto& newHoveredNode = getHoveredNodeOrChild(rootNode, cursorPosition);
		setHoveredNode(newHoveredNode);
	}

	void Application::pushTreeFocusableElements(const std::shared_ptr<ElementTreeNode>& node) {
		auto nodeElementFocusable = std::dynamic_pointer_cast<elements::Focusable>(node->element);
		if (nodeElementFocusable != nullptr && nodeElementFocusable->isFocusAllowed()) {
			focusableElements.push_back(nodeElementFocusable);
		}

		for (const auto& child: node->children) {
			pushTreeFocusableElements(child);
		}
	}

	void Application::setFocusedElement(const std::shared_ptr<elements::Focusable>& newFocusedElement) {
		if (newFocusedElement == focusedElement) {
			return;
		}

		if (focusedElement) {
			auto blurEvent = std::make_shared<FocusEvent>(false);
			focusedElement->onEvent(blurEvent);

			focusedElement = nullptr;
		}

		if (newFocusedElement) {
			auto focusEvent = std::make_shared<FocusEvent>(true);
			newFocusedElement->onEvent(focusEvent);

			focusedElement = newFocusedElement;
		}
	}

	void Application::clearFocusedElementIfRemoved() {
		if (focusedElement == nullptr) {
			return;
		}

		for (const auto& element: focusableElements) {
			if (element == focusedElement) {
				return;
			}
		}

		setFocusedElement(nullptr);
	}

	void Application::clearFocusedElementIfPendingBlur() {
		if (focusedElement && focusedElement->isPendingBlur()) {
			setFocusedElement(nullptr);
		}
	}

	void Application::updateFocusableElements() {
		focusableElements.clear();

		pushTreeFocusableElements(rootNode);
		clearFocusedElementIfRemoved();
		clearFocusedElementIfPendingBlur();

		if (focusedElement == nullptr) {
			for (const auto& focusableElement: focusableElements) {
				if (focusableElement->isPendingFocus()) {
					setFocusedElement(focusableElement);
					break;
				}
			}
		}
	}

	void Application::focusNextFocusableElement() {
		if (focusedElement == nullptr) {
			if (!focusableElements.empty()) {
				setFocusedElement(focusableElements[0]);
			}

			return;
		}

		for (int i = 0; i < focusableElements.size(); i++) {
			if (focusableElements[i] == focusedElement) {
				if (i + 1 < focusableElements.size()) {
					setFocusedElement(focusableElements[i + 1]);
					return;
				}
			}
		}
	}

	void Application::focusPreviousFocusableElement() {
		if (focusedElement == nullptr) {
			if (!focusableElements.empty()) {
				setFocusedElement(focusableElements[0]);
			}

			return;
		}

		for (int i = 0; i < focusableElements.size(); i++) {
			if (focusableElements[i] == focusedElement) {
				if (i - 1 >= 0) {
					setFocusedElement(focusableElements[i - 1]);
					return;
				}
			}
		}
	}

	std::shared_ptr<ElementTreeNode> Application::getFocusedElementNode() {
		if (rootNode == nullptr) {
			return nullptr;
		}

		if (focusedElement == nullptr) {
			return nullptr;
		}

		auto focusedElementAsElement = std::dynamic_pointer_cast<Element>(focusedElement);
		if (focusedElementAsElement == nullptr) {
			return nullptr;
		}

		return rootNode->findElementNode(focusedElementAsElement);
	}
}

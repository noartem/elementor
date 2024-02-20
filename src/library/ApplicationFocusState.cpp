//
// Created by noartem on 06.02.2024.
//

#include "ApplicationFocusState.h"

namespace elementor {
	int ring(int i, unsigned n) {
		if (i > 0) return (n + i) % n;
		if (i < 0) return n - (-i % n);
		return 0;
	}

	int clamp(int i, int min, int max) {
		if (i < min) return min;
		if (i > max) return max;
		return i;
	}

	bool isNodePendingFocus(const std::shared_ptr<ApplicationTree::Node>& node) {
		auto elementFocusable = std::dynamic_pointer_cast<elements::Focusable>(node->getElement());
		return elementFocusable->isPendingFocus();
	}

	bool isNodePendingBlur(const std::shared_ptr<ApplicationTree::Node>& node) {
		auto elementFocusable = std::dynamic_pointer_cast<elements::Focusable>(node->getElement());
		return elementFocusable->isPendingBlur();
	}

	bool isFocusRelatedEvent(const std::shared_ptr<Event>& event) {
		return event->getName() == "keyboard"
			|| event->getName() == "char";
	}

	bool isGoToNextFocusableEvent(const std::shared_ptr<Event>& event) {
		auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
		return keyboardEvent != nullptr
			&& (keyboardEvent->action == KeyAction::Press || keyboardEvent->action == KeyAction::Repeat)
			&& !(keyboardEvent->mods & KeyModsShift)
			&& keyboardEvent->key == KeyboardKey::Tab;
	}

	bool isGoToPreviousFocusableEvent(const std::shared_ptr<Event>& event) {
		auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
		return keyboardEvent != nullptr
			&& (keyboardEvent->action == KeyAction::Press || keyboardEvent->action == KeyAction::Repeat)
			&& (keyboardEvent->mods & KeyModsShift)
			&& keyboardEvent->key == KeyboardKey::Tab;
	}

	void ApplicationFocusState::tick() {
		focusableNodes.clear();
		applicationTree->visit([this](const std::shared_ptr<ApplicationTree::Node>& node) {
			auto element = node->getElement();
			auto elementFocusable = std::dynamic_pointer_cast<elements::Focusable>(element);
			if (elementFocusable == nullptr) {
				return;
			}

			focusableNodes.push_back(node);
		});

		clearFocusedNodeIfRemoved();
		clearFocusedNodeIfPendingBlur();

		for (const auto& focusableNode: focusableNodes) {
			if (isNodePendingFocus(focusableNode)) {
				setFocusedNode(focusableNode);
			}
		}
	}

	EventCallbackResponse ApplicationFocusState::onEvent(const std::shared_ptr<Event>& event) {
		if (focusedNode && isFocusRelatedEvent(event)) {
			auto bubbleEventResponse = focusedNode->bubbleEvent(event);
			if (bubbleEventResponse == EventCallbackResponse::StopPropagation) {
				return EventCallbackResponse::StopPropagation;
			}
		}

		if (isGoToNextFocusableEvent(event)) {
			focusNextNode();
		} else if (isGoToPreviousFocusableEvent(event)) {
			focusPreviousNode();
		}

		return EventCallbackResponse::None;
	}

	int ApplicationFocusState::getFocusedNodeIndex() {
		if (focusedNode == nullptr) {
			return -1;
		}

		for (int i = 0; i < focusableNodes.size(); i++) {
			if (focusedNode->getElement() == focusableNodes[i]->getElement()) {
				return i;
			}
		}

		return -1;
	}

	void ApplicationFocusState::setFocusedNode(const std::shared_ptr<ApplicationTree::Node>& newFocusedNode) {
		if (focusedNode && newFocusedNode && focusedNode->getElement() == newFocusedNode->getElement()
			|| focusedNode == nullptr && newFocusedNode == nullptr) {
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

	void ApplicationFocusState::focusIthNode(int i) {
		if (focusableNodes.empty()) {
			return;
		}

		i = ring(i, focusableNodes.size());
		i = clamp(i, 0, focusableNodes.size() - 1);

		setFocusedNode(focusableNodes[i]);
	}

	void ApplicationFocusState::focusNextNode() {
		auto i = getFocusedNodeIndex();
		focusIthNode(i == -1 ? 0 : (i + 1));
	}

	void ApplicationFocusState::focusPreviousNode() {
		auto i = getFocusedNodeIndex();
		focusIthNode(i == -1 ? 0 : (i - 1));
	}

	void ApplicationFocusState::clearFocusedNodeIfRemoved() {
		if (focusedNode == nullptr) {
			return;
		}

		for (const auto& focusableNode: focusableNodes) {
			if (focusableNode->getElement() == focusedNode->getElement()) {
				return;
			}
		}

		setFocusedNode(nullptr);
	}

	void ApplicationFocusState::clearFocusedNodeIfPendingBlur() {
		if (focusedNode && isNodePendingBlur(focusedNode)) {
			setFocusedNode(nullptr);
		}
	}
}
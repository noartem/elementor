//
// Created by admin on 06.02.2024.
//

#include "HoverState.h"

namespace elementor {
	void HoverState::tick() {
		auto cursorPosition = cursor->getPosition();
		if (cursorPosition == InvalidPosition) {
			setHoveredNode(nullptr);
			return;
		}

		setHoveredNode(
			applicationTree->findDeepestNode(
				[=](const std::shared_ptr<ApplicationTree::Node>& node) {
					return node->getRect().contains(cursorPosition);
				}
			)
		);
	}

	bool isCursorCausedEvent(const std::shared_ptr<Event>& event) {
		return event->getName() == "mouse-button"
			|| event->getName() == "mouse-move"
			|| event->getName() == "scroll";
	}

	EventCallbackResponse HoverState::onEvent(const std::shared_ptr<Event>& event) {
		if (hoveredNode && isCursorCausedEvent(event)) {
			return hoveredNode->bubbleEvent(event);
		}

		return EventCallbackResponse::None;
	}

	void HoverState::setHoveredNode(const std::shared_ptr<ApplicationTree::Node>& newHoveredNode) {
		if (hoveredNode && newHoveredNode && hoveredNode->getElement() == newHoveredNode->getElement()
			|| hoveredNode == nullptr && newHoveredNode == nullptr) {
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
}
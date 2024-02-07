//
// Created by admin on 06.02.2024.
//

#ifndef ELEMENTOR_FOCUS_STATE_H
#define ELEMENTOR_FOCUS_STATE_H

#include <memory>
#include <optional>
#include <vector>

#include "Event.h"
#include "ApplicationContext.h"
#include "ApplicationTree.h"

#include "elements/Focusable.h"

namespace elementor {
	class FocusState {
	public:
		explicit FocusState(const std::shared_ptr<ApplicationTree>& applicationTree)
			: applicationTree(applicationTree) {
		}

		void tick();

		EventCallbackResponse onEvent(const std::shared_ptr<Event>& event);

	private:
		std::shared_ptr<ApplicationTree> applicationTree;

		std::vector<std::shared_ptr<ApplicationTree::Node>> focusableNodes = {};
		std::shared_ptr<ApplicationTree::Node> focusedNode = nullptr;

		void setFocusedNode(const std::shared_ptr<ApplicationTree::Node>& newFocusedNode);

		int getFocusedNodeIndex();

		void focusIthNode(int i);

		void focusNextNode();

		void focusPreviousNode();

		void clearFocusedNodeIfRemoved();

		void clearFocusedNodeIfPendingBlur();
	};
}

#endif //ELEMENTOR_FOCUS_STATE_H

//
// Created by noartem on 06.02.2024.
//

#ifndef ELEMENTOR_HOVER_STATE_H
#define ELEMENTOR_HOVER_STATE_H

#include <memory>
#include <optional>

#include "Event.h"
#include "ApplicationContext.h"
#include "ApplicationTree.h"

namespace elementor {
	class HoverState {
	public:
		HoverState(
			const std::shared_ptr<ApplicationTree>& applicationTree,
			const std::shared_ptr<Cursor>& cursor
		)
			: applicationTree(applicationTree), cursor(cursor) {
		}

		void tick();

		EventCallbackResponse onEvent(const std::shared_ptr<Event>& event);

	private:
		std::shared_ptr<ApplicationTree> applicationTree;
		std::shared_ptr<Cursor> cursor;

		std::shared_ptr<ApplicationTree::Node> hoveredNode = nullptr;

		void setHoveredNode(const std::shared_ptr<ApplicationTree::Node>& newHoveredNode);
	};
}

#endif //ELEMENTOR_HOVER_STATE_H

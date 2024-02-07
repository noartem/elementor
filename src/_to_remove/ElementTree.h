//
// Created by noartem on 09.01.2024.
//

#ifndef ELEMENTOR_ELEMENT_TREE_H
#define ELEMENTOR_ELEMENT_TREE_H

#include <memory>
#include <vector>
#include <map>

#include "Render.h"
#include "WindowContext.h"
#include "Element.h"
#include "Event.h"

namespace elementor {
	class ElementTreeNode : public std::enable_shared_from_this<ElementTreeNode> {
	public:
		ElementTreeNode(
			const std::shared_ptr<Element>& element,
			const ElementRect& rect,
			const std::shared_ptr<ElementTreeNode>& parent
		);

		static std::shared_ptr<ElementTreeNode> MakeRoot(
			const std::shared_ptr<Element>& element,
			const std::shared_ptr<WindowContext>& windowCtx
		);

		std::shared_ptr<ElementTreeNode> findElementNode(const std::shared_ptr<Element>& targetElement);

		EventCallbackResponse bubbleEvent(const std::shared_ptr<Event>& event) const;

		[[nodiscard]] std::shared_ptr<Element> getElement() const {
			return element;
		}

		[[nodiscard]] ElementRect getRect() const {
			return rect;
		}

		[[nodiscard]] std::shared_ptr<ElementTreeNode> getParent() const {
			return parent;
		}

		[[nodiscard]] std::vector<std::shared_ptr<ElementTreeNode>> getChildren() const {
			return children;
		}

		void addChild(const std::shared_ptr<ElementTreeNode>& child) {
			children.push_back(child);
		}

		std::vector<std::shared_ptr<EventHandler>> getEventHandlers(const std::string_view& eventName) const {
			if (!eventsHandlers.contains(eventName)) {
				return {};
			}

			return eventsHandlers.at(eventName);
		}

		std::vector<std::shared_ptr<EventHandler>> getGlobalEventsHandlers() const {
			return globalEventsHandlers;
		}

		EventCallbackResponse onEvent(const std::shared_ptr<Event>& event) const;

	private:
		std::shared_ptr<Element> element;
		ElementRect rect;
		std::shared_ptr<ElementTreeNode> parent;
		std::vector<std::shared_ptr<ElementTreeNode>> children;
		EventsHandlersMap eventsHandlers;
		std::vector<std::shared_ptr<EventHandler>> globalEventsHandlers;

		static std::shared_ptr<ElementTreeNode> Make(
			const std::shared_ptr<Element>& element,
			const ElementRect& rect,
			const std::shared_ptr<ElementTreeNode>& parent,
			const Rect& parentBoundary
		);
	};
}

#endif //ELEMENTOR_ELEMENT_TREE_H

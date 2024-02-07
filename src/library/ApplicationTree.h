//
// Created by admin on 04.02.2024.
//

#ifndef ELEMENTOR_APPLICATION_TREE_H
#define ELEMENTOR_APPLICATION_TREE_H

#include <memory>
#include <vector>
#include <map>
#include <iostream>

#include "Element.h"

namespace elementor {
	class ApplicationTree {
	public:
		class Node : public std::enable_shared_from_this<Node> {
			friend ApplicationTree;
		public:
			static std::shared_ptr<Node> New(
				const std::shared_ptr<Element>& element,
				const ElementRect& rect,
				const Rect& boundary,
				const std::shared_ptr<Node>& parent = nullptr
			);

			bool operator==(const Node& other) const {
				return element == other.element;
			}

			[[nodiscard]] const std::shared_ptr<Element>& getElement() const {
				return element;
			}

			[[nodiscard]] const Rect& getRect() const {
				return rect;
			}

			EventCallbackResponse onEvent(const std::shared_ptr<Event>& event);

			EventCallbackResponse bubbleEvent(const std::shared_ptr<Event>& event);

			void print(std::ostream& os, unsigned level = 0) const;

			void markChanged();

		private:
			std::shared_ptr<Element> element;
			ElementRect rect;
			Rect childBoundary;
			std::vector<std::shared_ptr<Node>> children;
			std::shared_ptr<Node> parent;

			std::vector<std::shared_ptr<EventHandler>> eventsHandlers;
			std::vector<std::shared_ptr<EventHandler>> globalEventsHandlers;

			bool changed = false;
			bool childrenChanged = false;

			std::shared_ptr<ApplicationTree::Node> findDeepestNode(
				const std::function<bool(const std::shared_ptr<Node>& node)>& predicate
			);

			void updateChildren();

			void draw(SkCanvas* canvas);
		};

		ApplicationTree(const std::shared_ptr<Element>& rootElement, const Size& rootSize);

		void print(std::ostream& os) const;

		void print() const {
			print(std::cout);
		}

		[[nodiscard]] std::shared_ptr<Node> findDeepestNode(
			const std::function<bool(const std::shared_ptr<Node>& node)>& predicate
		) const;

		[[nodiscard]] EventsHandlersMap getGlobalEventsHandlers() const;

		void visit(const std::function<void(const std::shared_ptr<Node>& node)>& visitor) const;

		void resize(const Size& size);

		void draw(SkCanvas* canvas);

		void markChanged();

		void updateChanged() const;

	private:
		std::shared_ptr<Node> root;
	};
}


#endif //ELEMENTOR_APPLICATION_TREE_H

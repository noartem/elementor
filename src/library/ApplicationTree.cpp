//
// Created by admin on 04.02.2024.
//

#include "ApplicationTree.h"
#include "debug.h"

#include <ranges>

namespace elementor {
	std::shared_ptr<ApplicationTree::Node> makeRootNode(
		const std::shared_ptr<Element>& rootElement,
		const Size& rootSize
	) {
		ElementRect rootRect{};
		rootRect.position = { 0, 0 };
		rootRect.inParentPosition = { 0, 0 };
		rootRect.size = rootSize;
		rootRect.visiblePosition = { 0, 0 };
		rootRect.visibleSize = rootSize;

		Rect rootBoundary{};
		rootBoundary.size = rootSize;
		rootBoundary.position = { 0, 0 };

		return ApplicationTree::Node::New(rootElement, rootRect, rootBoundary);
	}

	std::vector<std::shared_ptr<EventHandler>> getElementEventHandlers(const std::shared_ptr<Element>& element) {
		const auto& elementWithEventsHandlers = std::dynamic_pointer_cast<WithEventsHandlers>(element);
		if (!elementWithEventsHandlers) {
			return {};
		}

		return elementWithEventsHandlers->getEventsHandlers();
	}

	std::vector<std::shared_ptr<EventHandler>> getGlobalEventHandlers(const std::shared_ptr<Element>& element) {
		const auto& eventWithGlobalEventsHandlers = std::dynamic_pointer_cast<WithGlobalEventsHandlers>(element);
		if (!eventWithGlobalEventsHandlers) {
			return {};
		}

		return eventWithGlobalEventsHandlers->getGlobalEventsHandlers();
	}

	ApplicationTree::ApplicationTree(
		const std::shared_ptr<Element>& rootElement,
		const Size& rootSize
	) {
		root = makeRootNode(rootElement, rootSize);
	}

	void ApplicationTree::resize(const Size& newRootSize) {
		if (root->rect.size == newRootSize) {
			return;
		}

		root = makeRootNode(root->element, newRootSize);
	}

	void ApplicationTree::Node::print(std::ostream& os, unsigned int level) const {
		os << std::string(level * 2, ' ')
		   << "width=" << rect.size.width << ", "
		   << "height=" << rect.size.height << ", "
		   << "x=" << rect.position.x << ", "
		   << "y=" << rect.position.y
		   << std::endl;
	}

	void ApplicationTree::print(std::ostream& os) const {
		std::vector<std::pair<std::shared_ptr<Node>, int>> stack;
		stack.emplace_back(root, 0);
		while (!stack.empty()) {
			auto node = stack.back();
			stack.pop_back();

			node.first->print(os, node.second);

			for (auto& child: node.first->children) {
				stack.emplace_back(child, node.second + 1);
			}
		}
	}

	std::shared_ptr<ApplicationTree::Node> ApplicationTree::Node::findDeepestNode(
		const std::function<bool(const std::shared_ptr<Node>& node)>& predicate
	) {
		bool someChildMatched = false;
		for (const auto& child: children) {
			if (predicate(child)) {
				someChildMatched = true;
				break;
			}
		}

		if (!someChildMatched) {
			return shared_from_this();
		}

		for (const auto& child: children) {
			if (predicate(child)) {
				return child->findDeepestNode(predicate);
			}
		}

		return nullptr;
	}

	std::shared_ptr<ApplicationTree::Node> ApplicationTree::findDeepestNode(
		const std::function<bool(const std::shared_ptr<Node>& node)>& predicate
	) const {
		return root->findDeepestNode(predicate);
	}

	EventsHandlersMap ApplicationTree::getGlobalEventsHandlers() const {
		EventsHandlersMap eventsHandlers;

		std::vector<std::shared_ptr<Node>> stack;
		stack.push_back(root);
		while (!stack.empty()) {
			auto node = stack.back();
			stack.pop_back();

			for (const auto& eventHandler: node->globalEventsHandlers) {
				eventsHandlers[eventHandler->getName()].push_back(eventHandler);
			}

			for (auto& child: node->children) {
				stack.push_back(child);
			}
		}

		return eventsHandlers;
	}

	void ApplicationTree::visit(const std::function<void(const std::shared_ptr<Node>& node)>& visitor) const {
		std::vector<std::shared_ptr<Node>> stack;
		stack.push_back(root);
		while (!stack.empty()) {
			auto node = stack.back();
			stack.pop_back();

			visitor(node);

			for (auto& child: node->children | std::ranges::views::reverse) {
				stack.push_back(child);
			}
		}
	}

	void ApplicationTree::Node::draw(SkCanvas* canvas) {
		// TODO: Add cache
		// TODO: Rewrite without recursion

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
			canvas->clipRect(
				skRect,
				SkClipOp::kIntersect,
				clipBehavior == ClipBehavior::AntiAlias
			);
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
			child->draw(canvas);
		}

		canvas->restore();
	}

	void ApplicationTree::draw(SkCanvas* canvas) {
		root->draw(canvas);
	}

	void ApplicationTree::Node::markChanged() {
		childrenChanged = false;

		for (const auto& child: children) {
			child->markChanged();
			childrenChanged |= child->changed;
		}

		changed = element->popChanged();

		if (changed || childrenChanged) {
			// TODO: invalidate draw cache
		}
	}

	void ApplicationTree::markChanged() {
		root->changed = true;
		// TODO: Fix it
//		root->markChanged();
	}

	void ApplicationTree::Node::updateChildren() {
		children.clear();
		childrenChanged = false;

		for (const auto& childElementWithRect: element->getChildren(rect)) {
			auto childElement = std::get<0>(childElementWithRect);
			auto childRect = std::get<1>(childElementWithRect);

			ElementRect childElementRect{};
			childElementRect.size = childRect.size;
			childElementRect.position.x = rect.position.x + childRect.position.x;
			childElementRect.position.y = rect.position.y + childRect.position.y;
			childElementRect.inParentPosition = childRect.position;

			auto childVisibleRect = unionOfRects(childBoundary, childElementRect);
			childElementRect.visibleSize = childVisibleRect.size;
			childElementRect.visiblePosition = childVisibleRect.position;

			auto childNode = Node::New(childElement, childElementRect, childBoundary, shared_from_this());
			children.push_back(childNode);
		}
	}

	void ApplicationTree::updateChanged() const {
		if (root->changed) {
			root->updateChildren();
			return;
		}

		std::vector<std::shared_ptr<Node>> stack;
		stack.push_back(root);
		while (!stack.empty()) {
			auto node = stack.back();
			stack.pop_back();

			if (!node->changed && node->childrenChanged) {
				node->updateChildren();
				continue;
			}

			for (auto& child: node->children) {
				stack.push_back(child);
			}
		}
	}

	std::shared_ptr<ApplicationTree::Node> ApplicationTree::Node::New(
		const std::shared_ptr<Element>& element,
		const ElementRect& rect,
		const Rect& boundary,
		const std::shared_ptr<ApplicationTree::Node>& parent
	) {
		auto node = std::make_shared<Node>();
		node->element = element;
		node->parent = parent;
		node->rect = rect;
		node->childBoundary = element->getClipBehaviour() == ClipBehavior::None
							  ? boundary
							  : unionOfRects(boundary, rect);
		node->eventsHandlers = getElementEventHandlers(element);
		node->globalEventsHandlers = getGlobalEventHandlers(element);

		node->updateChildren();

		return node;
	}

	EventCallbackResponse ApplicationTree::Node::onEvent(const std::shared_ptr<Event>& event) {
		for (const auto& eventHandler: eventsHandlers) {
			auto response = eventHandler->onEvent(event);
			if (response != EventCallbackResponse::None) {
				return response;
			}
		}

		return EventCallbackResponse::None;
	}

	EventCallbackResponse ApplicationTree::Node::bubbleEvent(const std::shared_ptr<Event>& event) {
		std::shared_ptr<Node> currentNode = shared_from_this();

		while (currentNode != nullptr) {
			auto response = currentNode->onEvent(event);
			if (response != EventCallbackResponse::None) {
				return response;
			}

			currentNode = currentNode->parent;
		}

		return EventCallbackResponse::None;
	}
}

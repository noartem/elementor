//
// Created by noartem on 04.02.2024.
//

#include "ApplicationTree.h"
#include "debug.h"

#include <ranges>

#include <include/core/SkSurface.h>

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
		os << std::string(level * 2, '.');

		os << "(" << element << ") ";

		os << "[" << this << "] ";

		if (drawCachedImage != nullptr)
			os << "[[cached]] ";

		if (changed)
			os << "[[changed]] ";

		os << std::endl;

		for (const auto& child: children) {
			child->print(os, level + 1);
		}
	}

	std::shared_ptr<ApplicationTree::Node> ApplicationTree::Node::findFirstNode(
		const std::function<bool(const std::shared_ptr<Node>& node)>& predicate
	) {
		for (const auto& child: children) {
			if (predicate(child)) {
				return child;
			}
		}

		for (const auto& child: children) {
			auto childResult = child->findFirstNode(predicate);
			if (childResult) {
				return childResult;
			}
		}

		return nullptr;
	}

	std::shared_ptr<ApplicationTree::Node> ApplicationTree::findFirstNode(
		const std::function<bool(const std::shared_ptr<Node>& node)>& predicate
	) const {
		if (predicate(root)) {
			return root;
		}

		return root->findFirstNode(predicate);
	}

	std::shared_ptr<ApplicationTree::Node> ApplicationTree::Node::findLastNode(
		const std::function<bool(const std::shared_ptr<Node>& node)>& predicate
	) {
		bool someChildMatched = false;
		for (const auto& child: children | std::ranges::views::reverse) {
			if (predicate(child)) {
				someChildMatched = true;
				break;
			}
		}

		if (!someChildMatched) {
			return shared_from_this();
		}

		for (const auto& child: children | std::ranges::views::reverse) {
			if (predicate(child)) {
				return child->findLastNode(predicate);
			}
		}

		return nullptr;
	}

	std::shared_ptr<ApplicationTree::Node> ApplicationTree::findLastNode(
		const std::function<bool(const std::shared_ptr<Node>& node)>& predicate
	) const {
		return root->findLastNode(predicate);
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

	void ApplicationTree::Node::clipCanvas(SkCanvas* canvas) {
		ClipBehavior clipBehavior = element->getClipBehaviour();
		if (clipBehavior == ClipBehavior::None) {
			return;
		}

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

	void ApplicationTree::Node::draw(SkCanvas* canvas, bool withChildrenCache) {
		canvas->save();
		canvas->translate(rect.inParentPosition.x, rect.inParentPosition.y);
		clipCanvas(canvas);

		element->paintBackground(canvas, rect);

		for (const auto& child: children) {
			if (withChildrenCache) {
				child->drawWithCache(canvas);
			} else {
				child->draw(canvas, false);
			}
		}

		canvas->restore();
	}

	void ApplicationTree::Node::drawToCache(SkCanvas* canvas) {
		auto cacheSurface = canvas->makeSurface(canvas->imageInfo());
		auto cacheCanvas = cacheSurface->getCanvas();
		cacheCanvas->setMatrix(canvas->getTotalMatrix());

		draw(cacheCanvas, false);

		drawCachedImage = cacheSurface->makeImageSnapshot();

		drawCache(canvas);
	}

	void ApplicationTree::Node::drawCache(SkCanvas* canvas) {
		canvas->save();

		canvas->translate(rect.inParentPosition.x, rect.inParentPosition.y);
		clipCanvas(canvas);

		canvas->resetMatrix();
		canvas->drawImage(drawCachedImage, 0, 0);

		canvas->restore();
	}

	void ApplicationTree::Node::drawWithCache(SkCanvas* canvas) {
		if (drawCachedImage) {
			drawCache(canvas);
			return;
		}

		if (!childrenCached) {
			draw(canvas, true);
			return;
		}

		if (beforeCacheRenders > 0) {
			beforeCacheRenders -= 1;
			draw(canvas, false);
			return;
		}

		drawToCache(canvas);
	}

	void ApplicationTree::draw(SkCanvas* canvas) {
		root->drawWithCache(canvas);
	}

	void ApplicationTree::Node::removeCache() {
		drawCachedImage = nullptr;
		beforeCacheRenders = DEFAULT_BEFORE_CACHE_RENDERS;
	}

	void ApplicationTree::Node::removeCacheDeep() {
		removeCache();

		for (const auto& child: children) {
			child->removeCacheDeep();
		}
	}

	void ApplicationTree::Node::checkIfChanged() {
		changed = false;
		childrenChanged = false;
		deepChanged = false;
		childrenCached = true;

		for (const auto& child: children) {
			child->checkIfChanged();

			childrenChanged |= child->changed;
			childrenCached &= child->drawCachedImage != nullptr;

			deepChanged |= child->deepChanged;
		}

		changed = element->popChanged();
		deepChanged |= changed;

		D_IF_LOG(changed, "Element (" << element << ") changed");

		if (deepChanged) {
			removeCache();
		}
	}

	void ApplicationTree::checkIfChanged() {
		root->checkIfChanged();
	}

	void ApplicationTree::Node::updateChildren() {
		children.clear();
		childrenChanged = false;
		childrenCached = false;
		deepChanged = false;

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

			auto childNode = New(childElement, childElementRect, childBoundary, shared_from_this());
			children.push_back(childNode);
		}
	}

	bool ApplicationTree::Node::isChildrenChanged() {
		auto newChildren = element->getChildren(rect);

		if (children.size() != newChildren.size()) {
			return true;
		}

		for (size_t i = 0; i < children.size(); i++) {
			auto childOldElement = children[i]->element;
			auto childNewElement = std::get<0>(newChildren[i]);

			ElementRect childOldRect = children[i]->rect;
			auto childNewRect = std::get<1>(newChildren[i]);

			if (childOldElement != childNewElement ||
				childOldRect.size != childNewRect.size ||
				childOldRect.inParentPosition != childNewRect.position) {
				return true;
			}
		}

		return false;
	}

	void ApplicationTree::Node::updateChildrenIfChanged() {
		if (isChildrenChanged()) {
			updateChildren();
			return;
		}

		for (const auto& child: children) {
			child->updateChildrenIfChanged();
		}
	}

	void ApplicationTree::updateChanged() {
		if (root->deepChanged) {
			root->updateChildrenIfChanged();
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

		element->popChanged(); // fix setters called from constructor

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

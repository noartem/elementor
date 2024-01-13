//
// Created by admin on 12.01.2024.
//

#include "ElementTree.h"

#include <memory>
#include <vector>

#include "Render.h"
#include "WindowContext.h"
#include "Element.h"

namespace elementor {
	std::shared_ptr<ElementTreeNode> makeNode(
			const std::shared_ptr<Element>& element,
			const ElementRect& elementRect,
			const Rect& parentBoundary
	) {
		auto node = std::make_shared<ElementTreeNode>();
		node->element = element;
		node->rect = elementRect;

		Rect boundary = element->getClipBehaviour() == ClipBehavior::None
						? parentBoundary
						: unionOfRects(parentBoundary, elementRect);

		for (const auto& childElementWithRect: element->getChildren(elementRect)) {
			auto childElement = std::get<0>(childElementWithRect);
			auto childRect = std::get<1>(childElementWithRect);

			ElementRect childElementRect{};

			childElementRect.size = childRect.size;
			childElementRect.position.x = elementRect.position.x + childRect.position.x;
			childElementRect.position.y = elementRect.position.y + childRect.position.y;
			childElementRect.inParentPosition = childRect.position;

			auto childVisibleRect = unionOfRects(boundary, childElementRect);
			childElementRect.visibleSize = childVisibleRect.size;
			childElementRect.visiblePosition = childVisibleRect.position;

			auto childNode = makeNode(childElement, childElementRect, boundary);
			childNode->parent = node;
			node->children.push_back(childNode);
		}

		return node;
	}

	std::shared_ptr<ElementTreeNode> makeRootNode(
			const std::shared_ptr<Element>& element,
			const std::shared_ptr<WindowContext>& windowCtx
	) {
		ElementRect rootRect{};
		rootRect.position = { 0, 0 };
		rootRect.inParentPosition = { 0, 0 };
		rootRect.size = windowCtx->getSize();
		rootRect.visiblePosition = { 0, 0 };
		rootRect.visibleSize = windowCtx->getSize();

		Rect rootBoundary{};
		rootBoundary.position = { 0, 0 };
		rootBoundary.size = windowCtx->getSize();

		return makeNode(element, rootRect, rootBoundary);
	}
}
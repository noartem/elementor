//
// Created by admin on 09.01.2024.
//

#ifndef ELEMENTOR_ELEMENT_TREE_H
#define ELEMENTOR_ELEMENT_TREE_H

#include <memory>
#include <vector>

#include "Render.h"
#include "WindowContext.h"
#include "Element.h"

namespace elementor {
	struct ElementTreeNode {
		std::shared_ptr<Element> element;
		ElementRect rect{};
		std::vector<std::shared_ptr<ElementTreeNode>> children;
		std::weak_ptr<ElementTreeNode> parent;
	};

	std::shared_ptr<ElementTreeNode> makeNode(
			const std::shared_ptr<Element>& element,
			const ElementRect& elementRect,
			const Rect& parentBoundary
	);

	std::shared_ptr<ElementTreeNode> makeRootNode(
			const std::shared_ptr<Element>& element,
			const std::shared_ptr<WindowContext>& windowCtx
	);
}

#endif //ELEMENTOR_ELEMENT_TREE_H

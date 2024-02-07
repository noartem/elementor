//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_APPLICATION_APPLICATION_H
#define ELEMENTOR_APPLICATION_APPLICATION_H

#include "../include.h"
#include "../elements/Focusable.h"

#include "./ElementTree.h"

using namespace elementor;
using namespace elementor::elements;

namespace elementor::application {
	class Application : public ApplicationContext, public std::enable_shared_from_this<Application> {
	public:
		explicit Application(
			const std::shared_ptr<PlatformContext>& platformCtx,
			const std::shared_ptr<WindowContext>& windowCtx
		)
			: platformCtx(platformCtx), windowCtx(windowCtx) {
		}

		void draw(SkCanvas* canvas);

		void setRoot(const std::shared_ptr<Element>& rootElement) {
			root = rootElement;
		}

		void dispatch(const std::shared_ptr<Event>& event) {
			pendingEvents.push_back(event);
			platformCtx->requestNextFrame();
		}

		std::shared_ptr<WindowContext> getWindowCtx() override {
			return windowCtx;
		}

		std::shared_ptr<PlatformContext> getPlatformCtx() override {
			return platformCtx;
		}

	private:
		std::shared_ptr<PlatformContext> platformCtx;
		std::shared_ptr<WindowContext> windowCtx;

		std::shared_ptr<ApplicationContext> ctx;

		std::shared_ptr<Element> root;
		std::shared_ptr<ElementTreeNode> rootNode;

		std::vector<std::shared_ptr<Event>> pendingEvents;
		EventsHandlersMap eventsHandlers;

		std::shared_ptr<ElementTreeNode> hoveredNode;

		std::vector<std::shared_ptr<ElementTreeNode>> focusableNodes;
		std::shared_ptr<ElementTreeNode> focusedNode;

		void drawNode(const std::shared_ptr<ElementTreeNode>& node, SkCanvas* canvas);

		void dispatchPendingEvents();

		std::shared_ptr<ElementTreeNode> getHoveredNodeOrChild(
			const std::shared_ptr<ElementTreeNode>& node,
			const Position& cursorPosition
		) const;

		void setHoveredNode(const std::shared_ptr<ElementTreeNode>& newHoveredNode);

		void updateHoveredNode();

		void pushTreeFocusableNodes(const std::shared_ptr<ElementTreeNode>& node);

		void setFocusedNode(const std::shared_ptr<ElementTreeNode>& newFocusedNode);

		void clearFocusedNodeIfRemoved();

		void clearFocusedNodeIfPendingBlur();

		void updateFocusableNodes();

		int getFocusedNodeIndex();

		void focusIthNode(int i);

		void focusNextNode();

		void focusPreviousNode();

		void pushTreeGlobalEventsHandlers(const std::shared_ptr<ElementTreeNode>& node);

		void updateGlobalEventsHandlers();
	};
};


#endif //ELEMENTOR_APPLICATION_APPLICATION_H

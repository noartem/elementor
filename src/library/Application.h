//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_APPLICATION_H
#define ELEMENTOR_APPLICATION_H

#include <map>
#include <vector>
#include <memory>
#include <algorithm>

#include <include/core/SkCanvas.h>

#include "Render.h"
#include "Element.h"
#include "Event.h"
#include "ElementTree.h"
#include "WindowContext.h"
#include "PlatformContext.h"
#include "ApplicationContext.h"

#include "elements/Focusable.h"

namespace elementor {
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
			this->root = rootElement;
		}

		void emit(const std::shared_ptr<Event>& event) {
			this->pendingEvents.push_back(event);
		}

		std::shared_ptr<WindowContext> getWindowCtx() override {
			return windowCtx;
		}

		std::shared_ptr<PlatformContext> getPlatformCtx() override {
			return platformCtx;
		}

		int addEventListener(
			const std::string_view& eventName,
			const std::function<void(const std::shared_ptr<Event>& event)>& eventListener
		) override;

		void removeEventListener(const std::string_view& name, int eventListenerId) override;

	private:
		std::shared_ptr<PlatformContext> platformCtx;
		std::shared_ptr<WindowContext> windowCtx;

		std::shared_ptr<ApplicationContext> ctx;

		std::shared_ptr<Element> root;
		std::shared_ptr<ElementTreeNode> rootNode;

		std::vector<std::shared_ptr<Event>> pendingEvents;
		std::map<std::string_view, std::vector<std::function<void(const std::shared_ptr<Event>&)>>> eventsListeners;
		std::map<std::string_view, std::vector<int>> eventsListenersFreeIndexes;

		std::shared_ptr<ElementTreeNode> hoveredNode;

		std::vector<std::shared_ptr<elements::Focusable>> focusableElements;
		std::shared_ptr<elements::Focusable> focusedElement;

		void drawNode(const std::shared_ptr<ElementTreeNode>& node, SkCanvas* canvas);

		void dispatchPendingEvents();

		EventCallbackResponse bubbleEvent(const std::shared_ptr<ElementTreeNode>& elementNode, const std::shared_ptr<Event> &event) const;

		std::shared_ptr<ElementTreeNode> getHoveredNodeOrChild(const std::shared_ptr<ElementTreeNode>& node, const Position& cursorPosition) const;

		void setHoveredNode(const std::shared_ptr<ElementTreeNode>& newHoveredNode);

		void updateHoveredNode();

		void pushTreeFocusableElements(const std::shared_ptr<ElementTreeNode>& node);

		void setFocusedElement(const std::shared_ptr<elements::Focusable>& newFocusedElement);

		void clearFocusedElementIfRemoved();

		void updateFocusableElements();

		void focusNextFocusableElement();

		void focusPreviousFocusableElement();

		std::shared_ptr<ElementTreeNode> getFocusedElementNode();
	};
};


#endif //ELEMENTOR_APPLICATION_H

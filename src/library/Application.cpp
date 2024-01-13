//
// Created by noartem on 13.04.2022.
//

#include "Application.h"

#include <memory>

#include <include/core/SkCanvas.h>

#include "Element.h"
#include "ElementTree.h"
#include "Event.h"

namespace elementor {
	template<typename T, typename... U>
	size_t getAddress(std::function<T(U...)> f) {
		typedef T(fnType)(U...);
		auto** fnPointer = f.template target<fnType*>();
		return (size_t)*fnPointer;
	}

	void Application::draw(SkCanvas* canvas) {
		this->dispatchPendingEvents();

		this->rootNode = makeRootNode(this->root, windowCtx);
		this->drawNode(this->rootNode, canvas);
	}

	void Application::drawNode(const std::shared_ptr<ElementTreeNode>& node, SkCanvas* canvas) {
		canvas->save();
		canvas->translate(node->rect.inParentPosition.x, node->rect.inParentPosition.y);

		ClipBehavior clipBehavior = node->element->getClipBehaviour();
		if (clipBehavior != ClipBehavior::None) {
			SkRect rect = SkRect::MakeXYWH(
					node->rect.visiblePosition.x - node->rect.position.x,
					node->rect.visiblePosition.y - node->rect.position.y,
					node->rect.visibleSize.width,
					node->rect.visibleSize.height
			);
			canvas->clipRect(rect, SkClipOp::kIntersect, clipBehavior == ClipBehavior::Hard);
		}

		node->element->paintBackground(canvas, node->rect);

#ifdef DEBUG
		SkPaint debugPaint;
		debugPaint.setColor(SK_ColorRED);
		debugPaint.setStrokeWidth(2);
		debugPaint.setStyle(SkPaint::kStroke_Style);
		debugPaint.setAntiAlias(true);

		SkRect debugRect = SkRect::MakeWH(node->rect.visibleSize.width, node->rect.visibleSize.height);
		canvas->drawRect(debugRect, debugPaint);
#endif

		for (const auto& child: node->children) {
			drawNode(child, canvas);
		}

		canvas->restore();
	}

	EventCallbackResponse callElementEventHandler(
			const std::shared_ptr<Element>& element,
			const std::shared_ptr<Event>& event
	) {
		auto elementEventHandler = dynamic_cast<WithEvents*>(element.get());
		if (elementEventHandler == nullptr) {
			return EventCallbackResponse::None;
		}

		return elementEventHandler->onEvent(event);
	}

	void Application::dispatchPendingEvents() {
		auto lastPendingEvents = pendingEvents;
		pendingEvents = {};

		for (const auto& event: lastPendingEvents) {
			auto eventListeners = eventsListeners[event->getName()];
			for (const auto& listener: eventListeners) {
				listener(event);
			}
		}
	}

	void Application::addEventListener(
			const std::string_view& eventName,
			const std::function<void(const std::shared_ptr<Event>&)>& listener
	) {
		eventsListeners[eventName].push_back(listener);
	}

	void Application::removeEventListener(
			const std::string_view& name,
			const std::function<void(const std::shared_ptr<Event>&)>& listener
	) {
		auto eventListeners = eventsListeners[name];
		if (eventListeners.empty()) {
			return;
		}

		for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it) {
			if (getAddress(*it) == getAddress(listener)) {
				eventListeners.erase(it);
				break;
			}
		}
	}
}

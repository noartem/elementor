//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_DRAGGABLE_H
#define ELEMENTOR_DRAGGABLE_H

#include "../include.h"

namespace elementor::elements {
	struct DraggableProps {
		std::optional<std::function<bool(Position position, Position absolutePosition)>> onStart;
		std::optional<std::function<void(Position position, Position absolutePosition)>> onEnd;
		std::optional<std::function<void(Position position, Position absolutePosition, Position diff)>> onMove;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Draggable : public Element, public WithChild, public WithEventsHandlers, public WithGlobalEventsHandlers {
	public:
		using StartCallback = std::function<bool(Position position, Position absolutePosition)>;
		using EndCallback = std::function<void(Position position, Position absolutePosition)>;
		using MoveCallback = std::function<void(Position position, Position absolutePosition, Position diff)>;

		Draggable(const std::shared_ptr<ApplicationContext>& ctx, const DraggableProps& props)
			: Element(ctx) {
			if (props.onStart.has_value()) onStart(props.onStart.value());
			if (props.onEnd.has_value()) onEnd(props.onEnd.value());
			if (props.onMove.has_value()) onMove(props.onMove.value());
			setChild(props.child);
		}

		static std::shared_ptr<Draggable> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const DraggableProps& props
		) {
			return std::make_shared<Draggable>(ctx, props);
		}

		static std::shared_ptr<Draggable> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<Draggable>& elementRef,
			const DraggableProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<Draggable> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void onStart(const std::optional<StartCallback>& newCallback) {
			callbackStart = newCallback;
		}

		void onEnd(const std::optional<EndCallback>& newCallback) {
			callbackEnd = newCallback;
		}

		void onMove(const std::optional<MoveCallback>& newCallback) {
			callbackMove = newCallback;
		}

		void setChild(const std::shared_ptr<Element>& newChild) {
			markChanged();
			child = newChild;
		}

		Size getSize(const Boundaries& boundaries) override;

		void paintBackground(SkCanvas* canvas, const ElementRect& rect) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() override;

		std::vector<std::shared_ptr<EventHandler>> getGlobalEventsHandlers() override;

	private:
		ElementRect lastRect;
		Position cursorPosition;
		Position cursorAbsolutePosition;
		Position previousCursorAbsolutePosition;
		bool hovered;
		bool dragging;

		void onApplicationMouseMoveEvent(const std::shared_ptr<MouseMoveEvent>& event);

		void onApplicationMouseButtonEvent(const std::shared_ptr<MouseButtonEvent>& event);

		void onMouseButtonEvent(const std::shared_ptr<MouseButtonEvent>& event);

		std::optional<StartCallback> callbackStart;
		std::optional<EndCallback> callbackEnd;
		std::optional<MoveCallback> callbackMove;
	};
}


#endif //ELEMENTOR_DRAGGABLE_H

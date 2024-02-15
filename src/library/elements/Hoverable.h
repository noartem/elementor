//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_HOVERABLE_H
#define ELEMENTOR_HOVERABLE_H

#include "../include.h"

namespace elementor::elements {
	struct HoverableProps {
		std::optional<std::function<EventCallbackResponse()>> onEnter;
		std::optional<std::function<EventCallbackResponse()>> onLeave;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Hoverable : public Element, public WithEventsHandlers, public WithChild {
	public:
		Hoverable(const std::shared_ptr<ApplicationContext>& ctx, const HoverableProps& props)
			: Element(ctx) {
			if (props.onEnter.has_value()) onEnter(props.onEnter.value());
			if (props.onLeave.has_value()) onLeave(props.onLeave.value());
			setChild(props.child);
		}

		static std::shared_ptr<Hoverable> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const HoverableProps& props
		) {
			return std::make_shared<Hoverable>(ctx, props);
		}

		static std::shared_ptr<Hoverable> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<Hoverable>& elementRef,
			const HoverableProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<Hoverable> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void onEnter(const std::function<EventCallbackResponse()>& newCallbackEnter) {
			callbackEnter = newCallbackEnter;
		}

		void onLeave(const std::function<EventCallbackResponse()>& newCallbackLeave) {
			callbackLeave = newCallbackLeave;
		}

		void setChild(const std::shared_ptr <Element>& newChild) {
			markChanged();
			child = newChild;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() override;

	private:
		bool hovered;

		std::function<EventCallbackResponse()> callbackEnter;
		std::function<EventCallbackResponse()> callbackLeave;
	};
}


#endif //ELEMENTOR_HOVERABLE_H

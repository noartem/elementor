//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_CLICKABLE_H
#define ELEMENTOR_CLICKABLE_H

#include "../include.h"

namespace elementor::elements {
	struct ClickableProps {
		std::optional <std::function<EventCallbackResponse(KeyMod mod)>> onClick;
		std::optional <std::function<EventCallbackResponse(MouseButton button, KeyMod mod)>> onButton;
		const std::shared_ptr <Element>& child = nullptr;
	};

	class Clickable : public Element, public WithEventsHandlers, public WithChild {
	public:
		explicit Clickable(const std::shared_ptr <ApplicationContext>& ctx)
			: Element(ctx) {
		}

		Clickable(const std::shared_ptr <ApplicationContext>& ctx, const ClickableProps& props)
			: Element(ctx) {
			if (props.onClick.has_value()) onClick(props.onClick.value());
			if (props.onButton.has_value()) onButton(props.onButton.value());
			setChild(props.child);
		}

		static std::shared_ptr <Clickable> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			const ClickableProps& props
		) {
			return std::make_shared<Clickable>(ctx, props);
		}

		static std::shared_ptr <Clickable> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			std::shared_ptr <Clickable>& elementRef,
			const ClickableProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr <Clickable> New(const std::shared_ptr <ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void onClick(
			const std::optional <std::function<EventCallbackResponse(KeyMod mod)>>& newCallback
		) {
			callbackClick = newCallback;
		}

		void onButton(
			const std::optional <std::function<EventCallbackResponse(MouseButton button, KeyMod mod)>>& newCallback
		) {
			callbackButton = newCallback;
		}

		void setChild(const std::shared_ptr <Element>& newChild) {
			markChanged();
			child = newChild;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector <ElementWithRect> getChildren(const ElementRect& rect) override;

		std::vector <std::shared_ptr<EventHandler>> getEventsHandlers() override;

	private:
		bool hovered = false;

		std::optional <std::function<EventCallbackResponse(KeyMod mod)>> callbackClick;
		std::optional <std::function<EventCallbackResponse(MouseButton button, KeyMod mod)>> callbackButton;
	};
}


#endif //ELEMENTOR_CLICKABLE_H

//
// Created by noartem on 18.05.2022.
//

#ifndef ELEMENTOR_FOCUSABLE_H
#define ELEMENTOR_FOCUSABLE_H

#include "../Element.h"
#include "../Event.h"
#include "../WithChild.h"

namespace elementor::elements {
	struct FocusableProps {
		std::optional<std::function<void(bool focused)>> onFocusChange;
		std::optional<bool> canRequestFocus;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Focusable : public Element, public WithEvents, public WithChild {
	public:
		explicit Focusable(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx) {
		}

		Focusable(const std::shared_ptr<ApplicationContext>& ctx, const FocusableProps& props)
			: Element(ctx),
			  WithChild(props.child) {
			if (props.onFocusChange.has_value()) onFocusChange(props.onFocusChange.value());
			if (props.canRequestFocus.has_value()) setCanRequestFocus(props.canRequestFocus.value());
		}

		static std::shared_ptr<Focusable> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const FocusableProps& props
		) {
			return std::make_shared<Focusable>(ctx, props);
		}

		static std::shared_ptr<Focusable> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void onFocusChange(const std::optional<std::function<void(bool focused)>>& newCallback) {
			callbackFocusChange = newCallback;
		}

		[[nodiscard]] bool getCanRequestFocus() const {
			return canRequestFocus;
		}

		void setCanRequestFocus(bool newCanRequestFocus) {
			canRequestFocus = newCanRequestFocus;
		}

		[[nodiscard]] bool getPendingFocus() const {
			return pendingFocus;
		}

		void setPendingFocus(bool newPendingFocus) {
			pendingFocus = newPendingFocus;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		EventCallbackResponse onEvent(const std::shared_ptr<Event>& event) override;

	private:
		std::optional<std::function<void(bool focused)>> callbackFocusChange;
		bool canRequestFocus = true;
		bool pendingFocus = false;
	};
}


#endif //ELEMENTOR_FOCUSABLE_H

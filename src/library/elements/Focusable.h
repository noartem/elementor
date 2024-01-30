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

		[[nodiscard]] bool isFocusAllowed() const {
			return focusAllowed;
		}

		void disableFocus() {
			focusAllowed = false;
		}

		void enableFocus() {
			focusAllowed = true;
		}

		[[nodiscard]] bool isPendingBlur() const {
			return pendingBlur;
		}

		void blur() {
			pendingFocus = false;
			pendingBlur = true;
		}

		[[nodiscard]] bool isPendingFocus() const {
			return pendingFocus;
		}

		void focus() {
			pendingFocus = true;
			pendingBlur = false;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		EventCallbackResponse onEvent(const std::shared_ptr<Event>& event) override;

	private:
		bool focusAllowed = true;
		bool pendingFocus = false;
		bool pendingBlur = false;

		std::optional<std::function<void(bool focused)>> callbackFocusChange;
	};
}


#endif //ELEMENTOR_FOCUSABLE_H

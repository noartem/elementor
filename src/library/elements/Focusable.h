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

	class Focusable : public Element, public WithEventsHandlers, public WithChild {
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

		static std::shared_ptr<Focusable> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<Focusable>& elementRef,
			const FocusableProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
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
			if (!focused) {
				return;
			}

			pendingFocus = false;
			pendingBlur = true;
		}

		[[nodiscard]] bool isPendingFocus() const {
			return pendingFocus;
		}

		void focus() {
			if (focused) {
				return;
			}

			pendingFocus = true;
			pendingBlur = false;
		}

		[[nodiscard]] bool isFocused() const {
			return focused;
		}

		void setFocused(bool newFocused) {
			if (newFocused) {
				focus();
			} else {
				blur();
			}
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() override;

	private:
		bool focusAllowed = true;
		bool focused = false;
		bool pendingFocus = false;
		bool pendingBlur = false;

		std::optional<std::function<void(bool focused)>> callbackFocusChange;
	};
}


#endif //ELEMENTOR_FOCUSABLE_H

//
// Created by noartem on 02.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_CLICKABLE_OUTSIDE_H
#define ELEMENTOR_COMPONENTS_CLICKABLE_OUTSIDE_H

#include "utility.h"
#include "elementor.h"

#include "./Eventable.h"

namespace elementor::components {
	struct ClickableOutsideProps {
		std::optional <std::function<void()>> onClickOutside;
		const std::shared_ptr <Element>& child = nullptr;
	};

	class ClickableOutside : public Component {
	public:
		explicit ClickableOutside(const std::shared_ptr <ApplicationContext>& ctx, const ClickableOutsideProps& props)
			: Component(ctx) {
			element = Eventable::New(ctx, {
				.globalEvents = {
					MouseButtonEvent::Handle([this](const auto& event) {
						if (!hovered &&
							event->button == MouseButton::Left &&
							event->action == KeyAction::Release &&
							clickOutsideCallback.has_value()) {
							clickOutsideCallback.value()();
						}

						return EventCallbackResponse::None;
					})
				},
				.child = Hoverable::New(ctx, hoverable, {
					.onEnter = [this]() {
						hovered = true;
						return EventCallbackResponse::None;
					},
					.onLeave = [this]() {
						hovered = false;
						return EventCallbackResponse::None;
					},
				}),
			});

			if (props.onClickOutside.has_value()) onClickOutsize(props.onClickOutside.value());
			if (props.child) setChild(props.child);
		}

		static std::shared_ptr <ClickableOutside> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			const ClickableOutsideProps& props
		) {
			return std::make_shared<ClickableOutside>(ctx, props);
		}

		static std::shared_ptr<ClickableOutside> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<ClickableOutside>& elementRef,
			const ClickableOutsideProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr <ClickableOutside> New(const std::shared_ptr <ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void onClickOutsize(const std::function<void()>& callback) {
			clickOutsideCallback = callback;
		}

		void setChild(const std::shared_ptr <Element>& child) {
			markChanged();
			hoverable->setChild(child);
		}

	private:
		bool hovered = false;
		std::shared_ptr <Hoverable> hoverable;

		std::optional <std::function<void()>> clickOutsideCallback;
	};
}

#endif //ELEMENTOR_COMPONENTS_CLICKABLE_OUTSIDE_H

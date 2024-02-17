//
// Created by noartem on 02.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_BUTTON_H
#define ELEMENTOR_COMPONENTS_BUTTON_H

#include "utility.h"
#include "elementor.h"

#include "./ClickableOutside.h"
#include "./Cursorable.h"
#include "./Outline.h"

namespace elementor::components {
	class Button : public Component, public WithEventsHandlers {
	public:
		struct Props {
			std::optional<std::function<EventCallbackResponse()>> onClick;
			std::optional<std::function<EventCallbackResponse()>> onMiddleClick;
			std::shared_ptr<Element> child;
		};

		explicit Button(const std::shared_ptr<ApplicationContext>& ctx, const Props& props)
			: Component(ctx) {

			element = Outline::New(ctx, {
				.border = {
					.radius = 6,
					.width = 3,
					.color = "#21CFFF",
					.style = BorderStyle::Dashed,
				},
				.offset = 6,
				.child = Focusable::New(ctx, focusable, {
					.child = Cursorable::New(ctx, {
						.cursorShape = CursorShape::Hand,
						.child = ClickableOutside::New(ctx, {
							.onClickOutside = [this]() {
								blur();
							},
							.child = Clickable::New(ctx, {
								.onButton = [this](MouseButton button, int _) {
									if (button == MouseButton::Middle) {
										if (callbackMiddleClick.has_value()) {
											return callbackMiddleClick.value()();
										}
									}

									if (button != MouseButton::Left) {
										return EventCallbackResponse::None;
									}

									focus();

									if (!callbackClick.has_value()) {
										return EventCallbackResponse::None;
									}

									return callbackClick.value()();
								},
								.child = props.child
							})
						})
					})
				})
			});

			onClick(props.onClick);
			onMiddleClick(props.onMiddleClick);
		}

		static std::shared_ptr<Button> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const Props& props
		) {
			return std::make_shared<Button>(ctx, props);
		}

		static std::shared_ptr<Button> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<Button>& elementRef,
			const Props& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<Button> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void onClick(const std::optional<std::function<EventCallbackResponse()>>& newCallback) {
			callbackClick = newCallback;
		}

		void onMiddleClick(const std::optional<std::function<EventCallbackResponse()>>& newCallback) {
			callbackMiddleClick = newCallback;
		}

		void focus() {
			focusable->focus();
		}

		void blur() {
			focusable->blur();
		}

		std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() override {
			return {
				KeyboardEvent::Handle([this](const auto& event) {
					if (event->key == KeyboardKey::Escape &&
						event->action == KeyAction::Release) {
						blur();
						return EventCallbackResponse::StopPropagation;
					}

					if ((event->key == KeyboardKey::Space || event->key == KeyboardKey::Enter) &&
						event->action == KeyAction::Release &&
						callbackClick.has_value()) {
						return callbackClick.value()();
					}

					return EventCallbackResponse::None;
				})
			};
		};

	private:
		std::shared_ptr<Focusable> focusable = nullptr;

		std::optional<std::function<EventCallbackResponse()>> callbackClick;
		std::optional<std::function<EventCallbackResponse()>> callbackMiddleClick;
	};
}

#endif //ELEMENTOR_COMPONENTS_BUTTON_H

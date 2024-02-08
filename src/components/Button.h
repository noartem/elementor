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
	struct ButtonProps {
		std::optional<std::string> text;
		std::optional<std::string> fontColor;
		std::optional<std::string> backgroundColor;
		std::optional<std::string> outlineColor;
		std::optional<std::function<EventCallbackResponse()>> onClick;
	};

	class Button : public Component, public WithEventsHandlers {
	public:
		explicit Button(const std::shared_ptr<ApplicationContext>& ctx, const ButtonProps& props)
			: Component(ctx) {
			element = Outline::New(ctx, {
				.border = {
					.radius = 6,
					.width = 3,
					.color = props.outlineColor.value_or(props.fontColor.value_or("")),
					.style = BorderStyle::Dashed,
				},
				.offset = 6,
				.child = Focusable::New(ctx, focusable, {
					.onFocusChange = [this](bool newFocused) {
						setFocused(newFocused);
					},
					.child = Cursorable::New(ctx, {
						.cursorShape = CursorShape::Hand,
						.child = ClickableOutside::New(ctx, {
							.onClickOutside = [this]() {
								blur();
							},
							.child = Clickable::New(ctx, {
								.onClick = [this](KeyMod _) {
									focus();

									if (!callbackClick.has_value()) {
										return EventCallbackResponse::None;
									}

									return callbackClick.value()();
								},
								.child = Rounded::New(ctx, {
									.all = 4,
									.child = Background::New(ctx, {
										.color = props.backgroundColor,
										.child = Padding::New(ctx, {
											.all = 8,
											.top = 6,
											.child = Text::New(ctx, text, {
												.text = props.text,
												.fontColor = props.fontColor,
												.fontSize = 16,
												.fontFamily = "Arial",
											})
										})
									})
								})
							})
						})
					})
				})
			});

			if (props.onClick.has_value()) onClick(props.onClick.value());
		}

		static std::shared_ptr<Button> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const ButtonProps& props
			) {
			return std::make_shared<Button>(ctx, props);
		}

		static std::shared_ptr<Button> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<Button>& elementRef,
			const ButtonProps& props
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

		void setText(const std::string& newText) {
			text->setText(newText);
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
		bool focused = false;

		std::shared_ptr<Text> text = nullptr;
		std::shared_ptr<Focusable> focusable = nullptr;

		std::optional<std::function<EventCallbackResponse()>> callbackClick;

		void setFocused(bool newFocused) {
			markChanged();
			focused = newFocused;
		}
	};
}

#endif //ELEMENTOR_COMPONENTS_BUTTON_H

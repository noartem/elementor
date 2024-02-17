//
// Created by noartem on 04.02.2024.
//

#ifndef ELEMENTOR_COMPONENTS_TEXTINPUT_H
#define ELEMENTOR_COMPONENTS_TEXTINPUT_H

#include "utility.h"
#include "elementor.h"

#include "./ClickableOutside.h"
#include "./Cursorable.h"
#include "./Outline.h"

namespace elementor::components {
	class TextInput : public Component, public WithEventsHandlers {
	public:
		struct Props {
			std::u32string value;
			std::u32string placeholder;
			std::function<void(const std::u32string& value)> onChange;
			std::function<void(const std::u32string& value)> onInput;
			std::function<void(const std::u32string& value)> onSubmit;
		};

		explicit TextInput(const std::shared_ptr<ApplicationContext>& ctx, const Props& props)
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
					.onFocusChange = [this](bool focused) {
						setInputFocused(focused);
					},
					.child = Cursorable::New(ctx, {
						.cursorShape = CursorShape::IBeam,
						.child = ClickableOutside::New(ctx, {
							.onClickOutside = [this]() {
								blur();
							},
							.child = Clickable::New(ctx, {
								.onClick = [this](int _) {
									focus();
									return EventCallbackResponse::StopPropagation;
								},
								.child = Rounded::New(ctx, {
									.all = 6,
									.child = Background::New(ctx, background, {
										.color = "#ebf0f0",
										.child = Padding::New(ctx, {
											.all = 6,
											.child = Paragraph::New(ctx, paragraph, {
												.children = {
													Text::New(ctx, text, {
														.fontColor = "#000",
														.fontSize = 14,
														.fontFamily = "Arial",
													})
												}
											})
										})
									})
								})
							})
						})
					})
				})
			});

			setPlaceholder(props.placeholder);
			setValue(props.value);
			setOnChange(props.onChange);
			setOnInput(props.onInput);
			setOnSubmit(props.onSubmit);
		}

		static std::shared_ptr<TextInput> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const Props& props
		) {
			return std::make_shared<TextInput>(ctx, props);
		}

		static std::shared_ptr<TextInput> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<TextInput>& elementRef,
			const Props& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<TextInput> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void blur() {
			focusable->blur();
		}

		void focus() {
			focusable->focus();
		}

		std::string getValue() {
			return toUTF8(value);
		}

		void setPlaceholder(const std::u32string& newValue) {
			placeholder = newValue;
			updateText();
		}

		void setValue(const std::u32string& newValue) {
			value = newValue;

			updateText();

			if (changeCallback) {
				changeCallback(value);
			}
		}

		void setValue(const std::string& newValue) {
			setValue(fromUTF8(newValue));
		}

		void setOnChange(const std::function<void(const std::u32string&)>& onChange) {
			changeCallback = onChange;
		}

		void setOnInput(const std::function<void(const std::u32string&)>& onInput) {
			inputCallback = onInput;
		}

		void setOnSubmit(const std::function<void(const std::u32string&)>& onSubmit) {
			submitCallback = onSubmit;
		}

		std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() override {
			return {
				KeyboardEvent::Handle([this](const auto& event) {
					if (!inputFocused || event->key == KeyboardKey::Unknown) {
						return EventCallbackResponse::None;
					}

					if (event->action == KeyAction::Release) {
						return EventCallbackResponse::None;
					}

					if (event->key == KeyboardKey::Escape) {
						blur();
						return EventCallbackResponse::StopPropagation;
					}

					if (event->key == KeyboardKey::Enter) {
						if (inputCallback) {
							inputCallback(value);
						}

						if (submitCallback) {
							submitCallback(value);
						}

						blur();

						return EventCallbackResponse::StopPropagation;
					}

					if (event->key == KeyboardKey::C && event->mods & KeyModsCtrl) {
						ctx->getClipboard()->set(toUTF8(value));
						return EventCallbackResponse::StopPropagation;
					}

					if (event->key == KeyboardKey::V && event->mods & KeyModsCtrl) {
						auto clipboard = ctx->getClipboard();
						auto clipboardValueU8 = clipboard->get();

						setValue(value + fromUTF8(clipboard->get()));

						return EventCallbackResponse::StopPropagation;
					}

					if (event->key == KeyboardKey::Backspace || event->key == KeyboardKey::Delete) {
						if (value.empty()) {
							return EventCallbackResponse::StopPropagation;
						}

						setValue(value.substr(0, value.size() - 1));
					}

					return EventCallbackResponse::None;
				}),
				CharEvent::Handle([this](const auto& event) {
					if (!inputFocused) {
						return EventCallbackResponse::None;
					}

					setValue(value + event->value);

					return EventCallbackResponse::StopPropagation;
				})
			};
		}

	private:
		// TODO: Add cursor
		// TODO: Add selection

		std::u32string value;
		std::u32string placeholder;

		std::function<void(const std::u32string&)> changeCallback = nullptr;
		std::function<void(const std::u32string&)> inputCallback = nullptr;
		std::function<void(const std::u32string&)> submitCallback = nullptr;

		std::shared_ptr<Text> text = nullptr;
		std::shared_ptr<Paragraph> paragraph = nullptr;
		std::shared_ptr<Background> background = nullptr;
		std::shared_ptr<Focusable> focusable = nullptr;

		bool inputFocused = false;

		void setInputFocused(bool focused) {
			inputFocused = focused;

			if (!inputFocused && inputCallback) {
				inputCallback(value);
			}
		}

		void updateText() {
			if (value.empty() || value == U" ") {
				text->setText(placeholder.empty() ? " " : toUTF8(placeholder));
				text->setFontColor("#aaa");
			} else {
				text->setText(value.empty() ? " " : toUTF8(value));
				text->setFontColor("#000");
			}
		}
	};
}

#endif //ELEMENTOR_COMPONENTS_TEXTINPUT_H

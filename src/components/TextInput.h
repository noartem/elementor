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

	struct TextInputProps {
		std::u32string value;
	};

	class TextInput : public Component, public WithEventsHandlers {
	public:
		explicit TextInput(const std::shared_ptr<ApplicationContext>& ctx, const TextInputProps& props)
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
								.onClick = [this](KeyMod _) {
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

			setValue(props.value);
		}

		static std::shared_ptr<TextInput> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const TextInputProps& props
		) {
			return std::make_shared<TextInput>(ctx, props);
		}

		static std::shared_ptr<TextInput> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<TextInput>& elementRef,
			const TextInputProps& props
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

		void setValue(const std::u32string& newValue) {
			value = newValue;

			auto textValue = value.empty() ? " " : toUTF8(value);
			text->setText(textValue);
		}

		std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() override {
			return {
				KeyboardEvent::Handle([this](const auto& event) {
					if (!inputFocused) {
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
						setValue(value + U"\n");
						return EventCallbackResponse::StopPropagation;
					}

					if (event->key == KeyboardKey::C && event->mod == KeyMod::Control) {
						ctx->getClipboard()->set(toUTF8(value));
						return EventCallbackResponse::StopPropagation;
					}

					if (event->key == KeyboardKey::V && event->mod == KeyMod::Control) {
						auto clipboard = ctx->getClipboard();
						auto clipboardValueU8 = clipboard->get();

						std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
						std::u32string clipboardValueU32 = converter.from_bytes(clipboardValueU8.data());

						setValue(value + clipboardValueU32);

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

		std::shared_ptr<Text> text = nullptr;
		std::shared_ptr<Paragraph> paragraph = nullptr;
		std::shared_ptr<Background> background = nullptr;
		std::shared_ptr<Focusable> focusable = nullptr;

		bool inputFocused = false;

		void setInputFocused(bool focused) {
			inputFocused = focused;
		}
	};
}

#endif //ELEMENTOR_COMPONENTS_TEXTINPUT_H

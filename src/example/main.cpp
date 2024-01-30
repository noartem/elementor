//
// Created by noartem on 12.01.2024.
//

#include "elementor.h"

#include <format>
#include <filesystem>

std::filesystem::path getThisPath() {
	return std::filesystem::current_path()
		.append("..")
		.append("..")
		.append("..")
		.append("..")
		.append("src")
		.append("examples")
		.append("basic");
}

class LikeButton : public Component, public WithEvents {
public:
	explicit LikeButton(const std::shared_ptr<ApplicationContext>& ctx)
		: Component(ctx) {
		text = Text::New(ctx, {
			.text = "Лайкнуть",
			.fontColor = "fff",
			.fontSize = 16,
			.fontFamily = "Arial",
		});

		element = Focusable::New(ctx, {
			.onFocusChange = [this](bool focused) {
				buttonFocused = focused;
			},
			.child = Cursorable::New(ctx, {
				.cursorShape = CursorShape::Hand,
				.child = Clickable::New(ctx, {
					.onClick = [this](KeyMod _) mutable {
						incCount();
						return EventCallbackResponse::None;
					},
					.child = Rounded::New(ctx, {
						.all = 4,
						.child = Background::New(ctx, {
							.color = "ff5020",
							.child = Padding::New(ctx, {
								.all = 8,
								.top = 6,
								.child = text
							})
						})
					})
				})
			}) });
	}

	static std::shared_ptr<LikeButton> New(const std::shared_ptr<ApplicationContext>& ctx) {
		return std::make_shared<LikeButton>(ctx);
	}

	EventCallbackResponse onEvent(const std::shared_ptr<Event>& event) override {
		if (!buttonFocused) {
			return EventCallbackResponse::None;
		}

		auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
		if (keyboardEvent) {
			if (keyboardEvent->action == KeyAction::Release &&
				(keyboardEvent->key == KeyboardKey::Space || keyboardEvent->key == KeyboardKey::Enter)) {
				incCount();
				return EventCallbackResponse::StopPropagation;
			}
		}

		return EventCallbackResponse::None;
	}

private:
	int count = 0;
	bool buttonFocused = false;
	std::shared_ptr<Text> text = nullptr;

	void setCount(int newCount) {
		count = newCount;
		text->setText(std::format("Лайкнуть ({})", count));
	}

	void incCount() {
		setCount(count + 1);
	}

};

struct TextInputProps {
	std::u32string value;
};

class TextInput : public Component, public WithEvents {
public:
	explicit TextInput(const std::shared_ptr<ApplicationContext>& ctx, const TextInputProps& props)
		: Component(ctx) {
		text = Text::New(ctx, {
			.fontColor = "#000",
			.fontSize = 14,
			.fontFamily = "Arial",
		});

		paragraph = Paragraph::New(ctx, {
			.children = {
				text,
			}
		});

		auto input = Rounded::New(ctx, {
			.all = 6,
			.child = Background::New(ctx, {
				.color = "#ebf0f0",
				.child = Padding::New(ctx, {
					.all = 6,
					.child = paragraph
				})
			})
		});

		focusable = Focusable::New(ctx, {
			.onFocusChange = [this](bool focused) {
				setInputFocused(focused);
			},
			.child = input,
		});

		element = Clickable::New(ctx, {
			.onClick = [this](KeyMod _) {
				focus();

				return EventCallbackResponse::StopPropagation;
			},
			.child = focusable
		});

		setValue(props.value);
	}

	static std::shared_ptr<TextInput> New(const std::shared_ptr<ApplicationContext>& ctx, const TextInputProps& props) {
		return std::make_shared<TextInput>(ctx, props);
	}

	static std::shared_ptr<TextInput> New(const std::shared_ptr<ApplicationContext>& ctx) {
		return New(ctx, {});
	}

	EventCallbackResponse onEvent(const std::shared_ptr<Event>& event) override {
		if (!inputFocused) {
			return EventCallbackResponse::None;
		}

		auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(event);
		if (keyboardEvent) {
			auto shouldStop = onKeyboardEvent(keyboardEvent);
			if (shouldStop) {
				return EventCallbackResponse::StopPropagation;
			} else {
				return EventCallbackResponse::None;
			}
		}

		auto charEvent = std::dynamic_pointer_cast<CharEvent>(event);
		if (charEvent) {
			onCharEvent(charEvent);
			return EventCallbackResponse::StopPropagation;
		}

		return EventCallbackResponse::None;
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

		paragraph->forceUpdate();
	}

private:
	std::u32string value;

	std::shared_ptr<Focusable> focusable = nullptr;
	std::shared_ptr<Text> text = nullptr;
	std::shared_ptr<Paragraph> paragraph = nullptr;

	bool inputFocused = false;

	void setInputFocused(bool focused) {
		inputFocused = focused;

		// TODO: Add cursor
	}

	bool onKeyboardEvent(const std::shared_ptr<KeyboardEvent>& event) {
		if (event->action == KeyAction::Release) {
			return false;
		}

		if (event->key == KeyboardKey::Escape) {
			blur();
			return true;
		}

		if (event->key == KeyboardKey::Enter) {
			setValue(value + U"\n");
			return true;
		}

		if (event->key == KeyboardKey::C && event->mod == KeyMod::Control) {
			ctx->getPlatformCtx()->getClipboard()->set(toUTF8(value));
			return true;
		}

		if (event->key == KeyboardKey::V && event->mod == KeyMod::Control) {
			auto clipboard = ctx->getPlatformCtx()->getClipboard();
			auto clipboardValueU8 = clipboard->get();

			std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
			std::u32string clipboardValueU32 = converter.from_bytes(clipboardValueU8.data());

			setValue(value + clipboardValueU32);

			return true;
		}

		if (event->key == KeyboardKey::Backspace || event->key == KeyboardKey::Delete) {
			if (value.empty()) {
				return true;
			}

			setValue(value.substr(0, value.size() - 1));
		}

		return false;
	}

	void onCharEvent(const std::shared_ptr<CharEvent>& event) {
		setValue(value + event->value);
	}
};

std::shared_ptr<Element> Example(const std::shared_ptr<ApplicationContext>& ctx) {
	return (
		Background::New(ctx, {
			.color = "#fff",
			.child = Scrollable::New(ctx, {
				.direction = ScrollDirection::Vertical,
				.child = Padding::New(ctx, {
					.all = 24,
					.child = Align::New(ctx, {
						.coefficient = 0.5,
						.child = Flex::New(ctx, {
							.spacing = 8,
							.direction = FlexDirection::Column,
							.children = {
								FPSLabel::New(ctx),
								Background::New(ctx, {
									.color = "#0a0",
									.child = Padding::New(ctx, {
										.top = 15,
										.right = 13,
										.bottom = 20,
										.left = 10,
										.child = Text::New(ctx, {
											.text = "Hello, world!",
											.fontColor = "#fff",
											.fontSize = 32,
											.fontWeight = 700,
											.fontSlant = FontSlant::Italic,
											.fontFamily = "Fira Code",
										})
									})
								}),
								LikeButton::New(ctx),
								TextInput::New(ctx, {
									.value = U"How are you?"
								}),
								Paragraph::New(ctx, {
									.children = {
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 14,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 13,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 12,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 11,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 10,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
										Text::New(ctx, {
											.text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras eget commodo orci, id aliquam enim. Proin nec arcu lobortis dolor iaculis ornare. Suspendisse diam mauris, vulputate ac facilisis quis, laoreet ac eros. Maecenas faucibus enim id ipsum imperdiet, quis elementum turpis efficitur. Sed volutpat fermentum consectetur. Suspendisse quis libero a purus tristique semper. Sed at condimentum tortor, sed tempus erat. Donec hendrerit lobortis neque, vitae rutrum tortor dignissim eget. Etiam nec ultricies ex. Etiam luctus orci faucibus eleifend placerat. Integer suscipit metus id lorem mollis ultricies. Praesent vehicula, est eget dignissim pulvinar, lorem erat pretium nisi, sit amet malesuada mi nisl quis erat.\n",
											.fontSize = 9,
											.fontFamily = "Fira Code",
										}),
									}
								})
							}
						})
					})
				})
			})
		})
	);
}

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor Examples");
	window->setSize({ 920, 640 });
	window->setMinSize({ 630, 320 });
	platform->addWindow(window);

	auto application = std::make_shared<Application>(platform, window);
	window->setApplication(application);

	auto root = Example(application);
	application->setRoot(root);

	platform->run();
}
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

class LikeButton : public Component {
public:
	explicit LikeButton(const std::shared_ptr<ApplicationContext>& ctx)
		: Component(ctx) {
		element = Button::New(ctx, button, {
			.text = "Лайкнуть (0)",
			.fontColor = "#fff",
			.backgroundColor = "#ff5020",
			.outlineColor = "#21CFFF",
			.onClick = [this]() {
				incCount();
				return EventCallbackResponse::StopPropagation;
			}
		});
	}

	static std::shared_ptr<LikeButton> New(const std::shared_ptr<ApplicationContext>& ctx) {
		return std::make_shared<LikeButton>(ctx);
	}

private:
	int count = 0;

	std::shared_ptr<Button> button;

	void setCount(int newCount) {
		count = newCount;
		button->setText(std::format("Лайкнуть ({})", count));
	}

	void incCount() {
		setCount(count + 1);
	}
};

std::shared_ptr<Element> Example(const std::shared_ptr<ApplicationContext>& ctx) {
	return (
		Background::New(ctx, {
			.color = "#fff",
			.child = Scrollbar::New(ctx, {
				.thickness = 8,
				.spacing = 2,
				.thumb = Rounded::New(ctx, {
					.all = 8,
					.child = Background::New(ctx, {
						.color = "#0a0",
					})
				}),
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
									Flex::New(ctx, {
										.spacing = 8,
										.children = {
											LikeButton::New(ctx),
											LikeButton::New(ctx),
											LikeButton::New(ctx),
										}
									}),
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
										}
									})
								}
							})
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

	auto root = Example(window);
	window->setRoot(root);

	platform->run();
}
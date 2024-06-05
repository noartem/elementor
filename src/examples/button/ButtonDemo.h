//
// Created by admin on 08.05.2024.
//

#ifndef EXAMPLES_BUTTON_DEMO_H
#define EXAMPLES_BUTTON_DEMO_H

#include "../elementor.h"
#include "../assets/include.h"

class ButtonDemo : public Component {
public:
	explicit ButtonDemo(const std::shared_ptr<ApplicationContext>& ctx)
		: Component(ctx) {
		auto lipsumText = "Lorem ipsum dolor sit amet";

		element = Background::New(ctx, {
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
								.spacing = 2,
								.direction = FlexDirection::Column,
								.children = {
									TextButton::New(ctx, {
										.text = "Добавить",
										.fontColor = "#fff",
										.backgroundColor = "#ff5020",
									}),
									LikeButton::New(ctx),
									IconButton::New(ctx, {
										.src = asset("add.svg"),
									}),
									IconButton::New(ctx, {
										.src = asset("delete.svg"),
									})
								}
							})
						})
					})
				})
			})
		});
	}

	static std::shared_ptr<ButtonDemo> New(const std::shared_ptr<ApplicationContext>& ctx) {
		return std::make_shared<ButtonDemo>(ctx);
	}

private:
	class LikeButton : public Component {
	public:
		explicit LikeButton(const std::shared_ptr<ApplicationContext>& ctx)
			: Component(ctx) {
			element = TextButton::New(ctx, button, {
				.text = "Лайкнуть (0)",
				.fontColor = "#fff",
				.backgroundColor = "#ff5020",
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

		std::shared_ptr<TextButton> button;

		void setCount(int newCount) {
			count = newCount;
			button->setText(std::format("Лайкнуть ({})", count));
		}

		void incCount() {
			setCount(count + 1);
		}
	};
};

#endif //EXAMPLES_BUTTON_DEMO_H

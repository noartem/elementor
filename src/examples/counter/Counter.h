//
// Created by admin on 17.02.2024.
//

#ifndef EXAMPLES_COUNTER_H
#define EXAMPLES_COUNTER_H

#include "../elementor.h"

class Counter : public Component {
public:
explicit Counter(const std::shared_ptr<ApplicationContext>& ctx)
	: Component(ctx) {
	element = Background::New(ctx, {
		.color = "#fff",
		.child = Flex::New(ctx, {
			.spacing = 4,
			.alignment = FlexAlignment::Center,
			.crossAlignment = FlexCrossAlignment::Center,
			.children = {
				Rounded::New(ctx, {
					.all = 6,
					.child = Background::New(ctx, {
						.color = "#ebf0f0",
						.child = Padding::New(ctx, {
							.all = 8,
							.child = Width::New(ctx, {
								.width = 50,
								.child = Align::New(ctx, {
									.width = { 1, 1 },
									.child = Text::New(ctx, countText, {
										.text = std::to_string(count),
										.fontColor = "#000",
										.fontSize = 20,
										.fontFamily = "Comic Sans",
									})
								})
							})
						})
					})
				}),
				TextButton::New(ctx, {
					.text = "Count",
					.fontColor = "#fff",
					.backgroundColor = "#ff5020",
					.onClick = [this] {
						incCount();
						return EventCallbackResponse::None;
					}
				})
			}
		})
	});
}

	static std::shared_ptr<Counter> New(const std::shared_ptr<ApplicationContext>& ctx) {
		return std::make_shared<Counter>(ctx);
	}

private:
	int count = 0;

	std::shared_ptr<Text> countText;

	void setCount(int newValue) {
		count = newValue;
		countText->setText(std::to_string(count));
	}

	void incCount() {
		setCount(count + 1);
	}
};

#endif //EXAMPLES_COUNTER_H

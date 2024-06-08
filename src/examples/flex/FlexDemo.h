//
// Created by admin on 08.05.2024.
//

#ifndef EXAMPLES_FLEX_DEMO_H
#define EXAMPLES_FLEX_DEMO_H

#include "../elementor.h"

std::shared_ptr<Element>
Box(const std::shared_ptr<ApplicationContext>& ctx, std::string text) {
	return Rounded::New(ctx, {
		.all = 8,
		.child = Background::New(ctx, {
			.color = "#ff5020",
			.child = Align::New(ctx, {
				.coefficient = 0.5,
				.child = Padding::New(ctx, {
					.bottom = 4,
					.child = Text::New(ctx, {
						.text = text,
						.fontColor = "#fff",
						.fontSize = 14,
						.fontWeight = 700,
						.fontFamily = "Fira Code",
					})
				})
			})
		})
	});
}

class FlexDemo : public Component {
public:
	explicit FlexDemo(const std::shared_ptr<ApplicationContext>& ctx)
		: Component(ctx) {
		auto lipsumText = "Lorem ipsum dolor sit amet";

		element = Background::New(ctx, {
			.color = "#fff",
			.child = Padding::New(ctx, {
				.all = 24,
				.child = Align::New(ctx, {
					.coefficient = 0.5,
					.child = Flex::New(ctx, {
						.spacing = 8,
						.direction = FlexDirection::Column,
						.children = {
							Height::New(ctx, {
								.height = 50,
								.child = Flex::New(ctx, {
									.spacing = 8,
									.alignment = FlexAlignment::Stretch,
									.children = {
										Width::New(ctx, {
											.width = 100,
											.child = Box(ctx, "100px 50px"),
										}),
										Width::New(ctx, {
											.width = 150,
											.child = Box(ctx, "150px 50px"),
										}),
										Flexible::New(ctx, {
											.grow = 1,
											.child = Box(ctx, "1fl 50px"),
										})
									}
								}),
							}),
							Flexible::New(ctx, {
								.grow = 1,
								.child = Flex::New(ctx, {
									.spacing = 8,
									.alignment = FlexAlignment::Stretch,
									.children = {
										Flexible::New(ctx, {
											.grow = 1,
											.child = Box(ctx, "1fl 1fl")
										}),
										Flexible::New(ctx, {
											.grow = 2,
											.child = Box(ctx, "2fl 1lf")
										}),
										Flexible::New(ctx, {
											.grow = 3,
											.child = Box(ctx, "3fl 1fl")
										}),
									}
								}),
							}),
							Flexible::New(ctx, {
								.grow = 2,
								.child = Flex::New(ctx, {
									.spacing = 8,
									.alignment = FlexAlignment::Stretch,
									.children = {
										Flexible::New(ctx, {
											.grow = 2,
											.child = Box(ctx, "2fl 2fl")
										}),
										Flexible::New(ctx, {
											.grow = 2,
											.child = Box(ctx, "2fl 2lf")
										}),
										Width::New(ctx, {
											.width = 100,
											.child = Box(ctx, "100px 2lf"),
										}),
										Flexible::New(ctx, {
											.grow = 2,
											.child = Box(ctx, "2fl 2fl")
										}),
									}
								}),
							}),
						}
					})
				})
			})
		});
	}

	static std::shared_ptr<FlexDemo> New(const std::shared_ptr<ApplicationContext>& ctx) {
		return std::make_shared<FlexDemo>(ctx);
	}
};

#endif //EXAMPLES_FLEX_DEMO_H

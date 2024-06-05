//
// Created by admin on 08.05.2024.
//

#ifndef EXAMPLES_TEXT_DEMO_H
#define EXAMPLES_TEXT_DEMO_H

#include "../elementor.h"

class TextDemo : public Component {
public:
	explicit TextDemo(const std::shared_ptr<ApplicationContext>& ctx)
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
									Text::New(ctx, {
										.text = lipsumText,
										.fontSize = 12,
										.fontFamily = "Fira Code",
									}),
									Text::New(ctx, {
										.text = lipsumText,
										.fontSize = 14,
										.fontFamily = "Fira Code",
									}),
									Text::New(ctx, {
										.text = lipsumText,
										.fontSize = 16,
										.fontFamily = "Fira Code",
									}),
									Text::New(ctx, {
										.text = lipsumText,
										.fontSize = 18,
										.fontFamily = "Fira Code",
									}),
									Text::New(ctx, {
										.text = lipsumText,
										.fontSize = 20,
										.fontFamily = "Fira Code",
									}),
									Text::New(ctx, {
										.text = lipsumText,
										.fontSize = 22,
										.fontFamily = "Fira Code",
									}),
									Text::New(ctx, {
										.text = lipsumText,
										.fontSize = 22,
										.fontSlant = FontSlant::Italic,
										.fontFamily = "Fira Code",
									}),
									Text::New(ctx, {
										.text = lipsumText,
										.fontSize = 22,
										.fontWeight = 600,
										.fontSlant = FontSlant::Italic,
										.fontFamily = "Fira Code",
									}),
									Text::New(ctx, {
										.text = lipsumText,
										.fontSize = 22,
										.fontWeight = 1000,
										.fontSlant = FontSlant::Oblique,
										.fontFamily = "Fira Code",
									}),
								}
							})
						})
					})
				})
			})
		});
	}

	static std::shared_ptr<TextDemo> New(const std::shared_ptr<ApplicationContext>& ctx) {
		return std::make_shared<TextDemo>(ctx);
	}
};

#endif //EXAMPLES_TEXT_DEMO_H

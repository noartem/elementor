//
// Created by noartem on 12.01.2024.
//

#include "elementor.h"

#include <filesystem>

std::shared_ptr<Element> Box(const std::shared_ptr<ApplicationContext>& ctx) {
	return (
		Border::New(ctx, {
			.radius = 16,
			.width = 16,
			.color = "#aaa",
			.child = Rounded::New(ctx, {
				.all = 8,
				.child = Background::New(ctx, {
					.color = "#faa",
				})
			})
		})
	);
}

struct SizedProps {
	float width = 0;
	float height = 0;
	const std::shared_ptr<Element>& child = nullptr;
};

std::shared_ptr<Element> Sized(const std::shared_ptr<ApplicationContext>& ctx, const SizedProps& props) {
	return (
		Height::New(ctx, {
			.height = props.height,
			.child = Width::New(ctx, {
				.width = props.width,
				.child = props.child
			})
		})
	);
}

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

std::shared_ptr<Element> Example(const std::shared_ptr<ApplicationContext>& ctx) {
	auto hoverableBackground = Background::New(ctx, {
		.color = "#f00",
	});

	return (
		Background::New(ctx, {
			.color = "#fff",
			.child = Padding::New(ctx, {
				.all = 24,
				.child = Align::New(ctx, {
					.coefficient = 0.5,
					.child = Column::New(ctx, {
						.spacing = 8,
						.children = {
							Align::New(ctx, {
								.width = { 0 },
								.child = Background::New(ctx, {
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
								})
							}),
							Height::New(ctx, {
								.height = 100,
								.child = Rounded::New(ctx, {
									.all = 16,
									.child = FitCover::New(ctx, {
										.child = Image::New(ctx, {
											.src = getThisPath().append("cat.jpg").string(),
										}),
									})
								})
							}),
							Row::New(ctx, {
								.spacing = 8,
								.children = {
									Sized(ctx, {
										.width = 100,
										.height = 100,
										.child = SVG::New(ctx, {
											.src = getThisPath().append("cat.svg").string(),
										})
									}),
									Sized(ctx, {
										.width = 100,
										.height = 100,
										.child = SVG::New(ctx, {
											.src = getThisPath().append("cat-2.svg").string(),
										})
									}),
									Sized(ctx, {
										.width = 100,
										.height = 100,
										.child = SVG::New(ctx, {
											.src = getThisPath().append("cat.svg").string(),
										})
									}),
									Sized(ctx, {
										.width = 100,
										.height = 100,
										.child = SVG::New(ctx, {
											.src = getThisPath().append("cat-2.svg").string(),
										})
									}),
									Align::New(ctx, {
										.height = { 0 },
										.child = Width::New(ctx, {
											.width = 100,
											.child = Ratio::New(ctx, {
												.ratio = 3.0 / 1.65,
												.child = SVG::New(ctx, {
													.src = getThisPath().append("cat.svg").string(),
												})
											}),
										})
									})
								}
							}),
							Paragraph::New(ctx, {
								.children = {
									Text::New(ctx, {
										.text = "It supports emoji! Examples: 😊🌌🚀☄️\n",
										.fontColor = "#222",
										.fontSize = 18,
									}),
									Text::New(ctx, {
										.text = "And ligatures! Examples: == === !! != !== << >> --- || |- -|\n",
										.fontColor = "#0a0",
										.fontSize = 18,
										.fontFamily = "Fira Code",
									}),
									Text::New(ctx, {
										.text = "You also can insert some elements here, here is example: ",
										.fontColor = "#222",
										.fontSize = 18,
									}),
									Sized(ctx, {
										.width = 100,
										.height = 50,
										.child = Box(ctx)
									}),
									Text::New(ctx, {
										.text = " and it is inlined.",
										.fontColor = "#222",
										.fontSize = 18,
									}),
								}
							}),
							Align::New(ctx, {
								.width = { 0 },
								.child = Rounded::New(ctx, {
									.all = 8,
									.child = Sized(ctx, {
										.width = 100,
										.height = 100,
										.child = Background::New(ctx, {
											.color = "#aaa",
											.child = Hoverable::New(ctx, {
												.onEnter = [hoverableBackground]() {
													hoverableBackground->setColor("#a00");
													return EventCallbackResponse::None;
												},
												.onLeave = [hoverableBackground]() {
													hoverableBackground->setColor("#f00");
													return EventCallbackResponse::None;
												},
												.child = Padding::New(ctx, {
													.bottom = 24,
													.left = 24,
													.child = Hoverable::New(ctx, {
														.onLeave = [hoverableBackground]() {
															return EventCallbackResponse::StopPropagation;
														},
														.child = hoverableBackground,
													})
												})
											})
										})
									})
								})
							}),
							Stack::New(ctx, {
								.children = {
									Sized(ctx, {
										.width = 500,
										.height = 500,
										.child = Box(ctx)
									}),
									Sized(ctx, {
										.width = 400,
										.height = 200,
										.child = Box(ctx)
									}),
									Sized(ctx, {
										.width = 200,
										.height = 400,
										.child = Box(ctx)
									}),
									Sized(ctx, {
										.width = 150,
										.height = 200,
										.child = Box(ctx)
									})
								}
							})
						}
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
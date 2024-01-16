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
							Row::New(ctx, {
								.spacing = 8,
								.children = {
									Sized(ctx, {
										.width = 100,
										.height = 100,
										.child = Box(ctx),
									}),
									Sized(ctx, {
										.width = 200,
										.height = 100,
										.child = Box(ctx),
									})
								}
							}),
							Height::New(ctx, {
								.height = 100,
								.child = Flex::New(ctx, {
									.spacing = 8,
									.alignment = FlexAlignment::Center,
									.children = {
										Flexible::New(ctx, {
											.child = Rounded::New(ctx, {
												.all = 16,
												.child = FitCover::New(ctx, {
													.child = Image::New(ctx, {
														.src = getThisPath().append("cat.jpg").string(),
													}),
												})
											})
										}),
										Sized(ctx, {
											.width = 100,
											.height = 50,
											.child = Box(ctx),
										}),
										Flexible::New(ctx, {
											.child = Rounded::New(ctx, {
												.all = 16,
												.child = Background::New(ctx, {
													.color = "#f0f3f9",
													.child = FitContain::New(ctx, {
														.child = Image::New(ctx, {
															.src = getThisPath().append("cat.jpg").string(),
														}),
													})
												})
											})
										}),
										Sized(ctx, {
											.width = 100,
											.height = 100,
											.child = SVG::New(ctx, {
												.src = getThisPath().append("logo.svg").string(),
											})
										})
									}
								})
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
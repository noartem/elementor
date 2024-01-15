//
// Created by noartem on 12.01.2024.
//

#include "elementor.h"

std::shared_ptr<Element> example(const std::shared_ptr<ApplicationContext>& ctx) {
	return (
		Background::New(ctx, {
			.color = "#fff",
			.child = Padding::New(ctx, {
				.all = 12,
				.child = Align::New(ctx, {
					.coefficient = 0.5,
					.child = Border::New(ctx, {
						.radius = 16,
						.width = 16,
						.color = "#faa",
						.child = Rounded::New(ctx, {
							.all = 8,
							.child = Height::New(ctx, {
								.height = 100,
								.child = Width::New(ctx, {
									.width = 100,
									.child = Background::New(ctx, {
										.color = "#aaa",
									})
								})
							})
						})
					})
				}),
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

	auto root = example(application);
	application->setRoot(root);

	platform->run();
}
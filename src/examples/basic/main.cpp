//
// Created by noartem on 12.01.2024.
//

#include "elementor.h"

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor Examples");
	window->setSize({ 920, 640 });
	window->setMinSize({ 630, 320 });
	platform->addWindow(window);

	auto application = std::make_shared<Application>(platform, window);
	window->setApplication(application);

	auto root = Background::New(application, {
		.color = "#fff",
		.child = Background::New(application, {
			.color = "#faa",
		})
	});
	application->setRoot(root);

	platform->run();
}
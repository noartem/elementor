//
// Created by noartem on 12.01.2024.
//

#include "./Basic.h"

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor Examples");
	window->setSize({ 420, 320 });
	window->setMinSize({ 240, 180 });
	platform->addWindow(window);

	window->setRoot(
		Basic::New(window)
	);

	platform->run();
}
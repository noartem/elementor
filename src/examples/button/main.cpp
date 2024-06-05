//
// Created by noartem on 08.05.2024.
//

#include "./ButtonDemo.h"

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor: Button");
	window->setSize({ 420, 320 });
	window->setMinSize({ 240, 180 });
	platform->addWindow(window);

	window->setRoot(
		ButtonDemo::New(window)
	);

	platform->run();
}
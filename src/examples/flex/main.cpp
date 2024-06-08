//
// Created by noartem on 08.06.2024.
//

#include "./FlexDemo.h"

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor: Flexbox Layout");
	window->setSize({ 420, 320 });
	window->setMinSize({ 420, 320 });
	platform->addWindow(window);

	window->setRoot(
		FlexDemo::New(window)
	);

	platform->run();
}
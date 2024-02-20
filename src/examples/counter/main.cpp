//
// Created by noartem on 12.01.2024.
//

#include "./Counter.h"

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor: Counter");
	window->setSize({ 224, 64 });
	window->setMinSize({ 160, 64 });
	platform->addWindow(window);

	window->setRoot(
		Counter::New(window)
	);

	platform->run();
}
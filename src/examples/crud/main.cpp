//
// Created by noartem on 12.01.2024.
//

#include "./Crud.h"

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor: Counter");
	window->setSize({ 512, 256 });
	window->setMinSize({ 512, 256 });
	platform->addWindow(window);

	window->setRoot(
		Crud::New(window)
	);

	platform->run();
}
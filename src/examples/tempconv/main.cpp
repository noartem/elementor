//
// Created by noartem on 12.01.2024.
//

#include "./TempConv.h"

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor: Temperature Converter");
	window->setSize({ 384, 64 });
	window->setMinSize({ 384, 64 });
	platform->addWindow(window);

	window->setRoot(
		TempConv::New(window)
	);

	platform->run();
}
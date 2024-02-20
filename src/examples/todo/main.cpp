//
// Created by noartem on 15.02.2024.
//

#include "./Todo.h"

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor: TODO");
	window->setSize({ 320, 420 });
	window->setMinSize({ 240, 320 });
	platform->addWindow(window);

	window->setRoot(
		Todo::New(window, {
			.filename = asset("todo.md"),
		})
	);

	platform->run();
}
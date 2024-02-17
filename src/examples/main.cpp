//
// Created by noartem on 15.02.2024.
//

#include "elementor.h"

#include "./todo/Todo.h"
#include "./basic/Basic.h"

class Examples : public Component {
public:
	explicit Examples(const std::shared_ptr<ApplicationContext>& ctx)
		: Component(ctx) {
		element = Background::New(ctx, {
			.color = "#36419a",
			.child = Padding::New(ctx, {
				.all = 12,
				.child = Flex::New(ctx, {
					.spacing = 12,
					.children = {
						Flexible::New(ctx, {
							.grow = 1,
							.child = Rounded::New(ctx, {
								.all = 8,
								.child = Basic::New(ctx),
							})
						}),
						Flexible::New(ctx, {
							.grow = 1,
							.child = Rounded::New(ctx, {
								.all = 8,
								.child = Todo::New(ctx, {
									.filename = asset("todo.md"),
								}),
							})
						})
					}
				}),
			})
		});
	}

	static std::shared_ptr<Examples> New(const std::shared_ptr<ApplicationContext>& ctx) {
		return std::make_shared<Examples>(ctx);
	}
};

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor Examples");
	window->setSize({ 640, 920 });
	window->setMinSize({ 640, 920 });
	platform->addWindow(window);

	window->setRoot(
		Examples::New(window)
	);

	platform->run();
}
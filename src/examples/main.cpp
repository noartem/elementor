//
// Created by noartem on 15.02.2024.
//

#include "elementor.h"

#include "./basic/Basic.h"
#include "./button/ButtonDemo.h"
#include "./counter/Counter.h"
#include "./crud/Crud.h"
#include "./tempconv/Tempconv.h"
#include "./text/TextDemo.h"
#include "./todo/Todo.h"

class Examples : public Component {
public:
	struct Props {
		std::shared_ptr<GLPlatform> platform;
	};

	explicit Examples(const std::shared_ptr<ApplicationContext>& ctx, const Props& props)
		: Component(ctx) {
		platform = props.platform;

		element = Background::New(ctx, {
				.color = "#fff",
				.child = Flex::New(ctx, {
					.alignment = FlexAlignment::Stretch,
					.children = {
						Background::New(ctx, {
							.color = "#36419a",
							.child = Flex::New(ctx, {
								.spacing = 8,
								.direction = FlexDirection::Column,
								.alignment = FlexAlignment::Start,
								.crossAlignment = FlexCrossAlignment::SpaceBetween,
								.children = {
									Scrollable::New(ctx, {
										.direction = ScrollDirection::Vertical,
										.child = Padding::New(ctx, {
											.all = 8,
											.bottom = 0,
											.child = makeItemsNamesElement(),
										}),
									}),
									Padding::New(ctx, {
										.all = 8,
										.top = 0,
										.child = FPSLabel::New(ctx),
									})
								}
							}),
						}),
						Flexible::New(ctx, activeItemElementSlot, {
							.grow = 1,
						})
					}
				})
			}
		);
	}

	static std::shared_ptr<Examples> New(
		const std::shared_ptr<ApplicationContext>& ctx,
		const Props& props
	) {
		return std::make_shared<Examples>(ctx, props);
	}

private:
	std::shared_ptr<GLPlatform> platform;

	std::string activeItemName;
	std::shared_ptr<Flexible> activeItemElementSlot;

	const std::vector<std::pair<std::string, std::function<std::shared_ptr<Element>()>>> items = {
		{ "Basic", [this]() {
			return Basic::New(ctx);
		}},
		{ "Text", [this]() {
			return TextDemo::New(ctx);
		}},
		{ "Button", [this]() {
			return ButtonDemo::New(ctx);
		}},
		{ "Counter", [this]() {
			return Counter::New(ctx);
		}},
		{ "CRUD", [this]() {
			return Crud::New(ctx);
		}},
		{ "TempConv", [this]() {
			return TempConv::New(ctx);
		}},
		{ "Todo", [this]() {
			return Todo::New(ctx, {
				.filename = asset("todo.md"),
			});
		}}
	};

	std::vector<std::shared_ptr<Element>> makeItemsNamesElements() {
		std::vector<std::shared_ptr<Element>> itemsNamesElements;

		for (auto [name, makeElement]: items) {
			itemsNamesElements.push_back(
				TextButton::New(ctx, {
					.text = name,
					.fontColor = "#36419a",
					.backgroundColor = "#ffffff",
					.onClick = [this, name, makeElement]() {
						if (activeItemName != name) {
							activeItemName = name;
							activeItemElementSlot->setChild(makeElement());
						}
						return EventCallbackResponse::None;
					},
					.onMiddleClick = [this, name, makeElement]() {
						auto window = std::make_shared<GLWindow>(platform);
						window->setTitle(name);
						window->setSize({ 640, 920 });
						window->setMinSize({ 640, 920 });
						platform->addWindow(window);

						window->setRoot(
							makeElement()
						);

						return EventCallbackResponse::None;
					}
				})
			);
		}

		return itemsNamesElements;
	}

	std::shared_ptr<Element> makeItemsNamesElement() {
		return Flex::New(ctx, {
			.spacing = 8,
			.direction = FlexDirection::Column,
			.children = makeItemsNamesElements(),
		});
	}
};

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	window->setTitle("Elementor Examples");
	window->setSize({ 640, 320 });
	window->setMinSize({ 320, 320 });
	platform->addWindow(window);

	window->setRoot(
		Examples::New(window, {
			.platform = platform
		})
	);

	platform->run();
}
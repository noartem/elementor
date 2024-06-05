//
// Created by admin on 31.03.2024.
//

#define TEST

#include <fstream>

#include <include/core/SkImage.h>
#include <include/core/SkData.h>
#include <include/core/SkEncodedImageFormat.h>

#include "../src/examples/elementor.h"
#include "../src/examples/basic/Basic.h"
#include "../src/examples/button/ButtonDemo.h"
#include "../src/examples/counter/Counter.h"
#include "../src/examples/crud/Crud.h"
#include "../src/examples/tempconv/TempConv.h"
#include "../src/examples/text/TextDemo.h"
#include "../src/examples/todo/Todo.h"

struct Example {
	std::string name;
	Size size;
	std::function<std::shared_ptr<Element>(const std::shared_ptr<ApplicationContext>& ctx)> make;
};

const std::vector<Example> Examples = {
	{
		.name = "basic",
		.size = { 420, 320 },
		.make = [](const std::shared_ptr<ApplicationContext>& ctx) {
			return Basic::New(ctx);
		}
	},
	{
		.name = "button",
		.size = { 420, 320 },
		.make = [](const std::shared_ptr<ApplicationContext>& ctx) {
			return ButtonDemo::New(ctx);
		}
	},
	{
		.name = "counter",
		.size = { 256, 256 },
		.make = [](const std::shared_ptr<ApplicationContext>& ctx) {
			return Counter::New(ctx);
		}
	},
	{
		.name = "crud",
		.size = { 512, 256 },
		.make = [](const std::shared_ptr<ApplicationContext>& ctx) {
			return Crud::New(ctx);
		}
	},
	{
		.name = "tempconv",
		.size = { 384, 64 },
		.make = [](const std::shared_ptr<ApplicationContext>& ctx) {
			return TempConv::New(ctx);
		}
	},
	{
		.name = "text",
		.size = { 512, 256 },
		.make = [](const std::shared_ptr<ApplicationContext>& ctx) {
			return TextDemo::New(ctx);
		}
	},
	{
		.name = "todo",
		.size = { 320, 420 },
		.make = [](const std::shared_ptr<ApplicationContext>& ctx) {
			return Todo::New(ctx, {
				.filename = asset("test.md"),
			});
		}
	}
};

void saveImageToFile(const sk_sp<SkImage>& image, const std::string& filename) {
	sk_sp<SkData> encodedData = image->encodeToData(SkEncodedImageFormat::kPNG, 100);
	if (!encodedData) {
		return;
	}

	std::ofstream file(filename, std::ios::binary);
	if (!file) {
		return;
	}

	file.write(static_cast<const char*>(encodedData->data()), encodedData->size());

	file.close();
}

int main() {
	auto platform = std::make_shared<GLPlatform>();

	auto window = std::make_shared<GLWindow>(platform);
	platform->addWindow(window);

	for (const auto& example: Examples) {
		window->setSize(example.size);
		window->setRoot(example.make(window));
		platform->__T_tick(2);
		saveImageToFile(
			window->__T_screenshot(),
			"../../../../tests/screenshots_new/" + example.name + ".png"
		);
	}

	window->close();
}
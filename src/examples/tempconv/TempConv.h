//
// Created by admin on 17.02.2024.
//

#ifndef EXAMPLES_TEMP_CONV_H
#define EXAMPLES_TEMP_CONV_H

#include "../elementor.h"

float parseFloat(const std::string& value) {
	try {
		return std::stof(value);
	}
	catch (...) {
		return 0.0f;
	}
}

float parseFloat(const std::u32string& valueU32) {
	return parseFloat(toUTF8(valueU32));
}

class TempConv : public Component {
public:
	explicit TempConv(const std::shared_ptr<ApplicationContext>& ctx)
		: Component(ctx) {
		element = Background::New(ctx, {
			.color = "#fff",
			.child = Flex::New(ctx, {
				.spacing = 12,
				.alignment = FlexAlignment::Center,
				.crossAlignment = FlexCrossAlignment::Center,
				.children = {
					Flex::New(ctx, {
						.spacing = 4,
						.alignment = FlexAlignment::Center,
						.children = {
							Width::New(ctx, {
								.width = 100,
								.child = TextInput::New(ctx, textInputC, {
									.onInput = [this](const std::u32string& value) {
										setTempC(parseFloat(value));
									}
								}),
							}),
							Text::New(ctx, {
								.text = "Celsius",
								.fontColor = "#000",
								.fontSize = 14,
								.fontFamily = "Arial",
							}),
						}
					}),
					Text::New(ctx, {
						.text = "=",
						.fontColor = "#000",
						.fontSize = 14,
						.fontFamily = "Arial",
					}),
					Flex::New(ctx, {
						.spacing = 4,
						.alignment = FlexAlignment::Center,
						.children = {
							Width::New(ctx, {
								.width = 100,
								.child = TextInput::New(ctx, textInputF, {
									.onInput = [this](const std::u32string& value) {
										setTempF(parseFloat(value));
									}
								}),
							}),
							Text::New(ctx, {
								.text = "Fahrenheit",
								.fontColor = "#000",
								.fontSize = 14,
								.fontFamily = "Arial",
							}),
						}
					})
				}
			})
		});

		setTempC(0);
	}

	static std::shared_ptr<TempConv> New(const std::shared_ptr<ApplicationContext>& ctx) {
		return std::make_shared<TempConv>(ctx);
	}

private:
	float tempC = 0;
	float tempF = 0;

	std::shared_ptr<TextInput> textInputC;
	std::shared_ptr<TextInput> textInputF;

	void setTempC(float newValue) {
		tempC = newValue;
		textInputC->setValue(std::format("{:.2f}", tempC));

		tempF = tempC * 1.8f + 32.0f;
		textInputF->setValue(std::format("{:.2f}", tempF));
	}

	void setTempF(float newValue) {
		tempF = newValue;
		textInputF->setValue(std::format("{:.2f}", tempF));

		tempC = (tempF - 32.0f) / 1.8f;
		textInputC->setValue(std::format("{:.2f}", tempC));
	}
};

#endif //EXAMPLES_TEMP_CONV_H

//
// Created by noartem on 16.02.2024.
//

#ifndef ELEMENTOR_COMPONENTS_TEXT_BUTTON_H
#define ELEMENTOR_COMPONENTS_TEXT_BUTTON_H

#include "elementor.h"

#include "./Button.h"

namespace elementor::components {
	class TextButton : public Component {
	public:
		struct Props {
			std::optional<std::string> text;
			std::optional<std::string> fontColor;
			std::optional<std::string> backgroundColor;
			std::optional<std::function<EventCallbackResponse()>> onClick;
		};

		explicit TextButton(const std::shared_ptr<ApplicationContext>& ctx, const Props& props)
			: Component(ctx) {
			element = Button::New(ctx, {
				.onClick = props.onClick,
				.child = Rounded::New(ctx, {
					.all = 4,
					.child = Background::New(ctx, {
						.color = props.backgroundColor,
						.child = Padding::New(ctx, {
							.all = 8,
							.top = 6,
							.child = Text::New(ctx, text, {
								.text = props.text,
								.fontColor = props.fontColor,
								.fontSize = 16,
								.fontFamily = "Arial",
							}),
						})
					})
				})
			});
		}

		static std::shared_ptr<TextButton> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const Props& props
		) {
			return std::make_shared<TextButton>(ctx, props);
		}

		static std::shared_ptr<TextButton> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<TextButton>& elementRef,
			const Props& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<TextButton> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setText(const std::string& newText) {
			text->setText(newText);
		}

	private:
		std::shared_ptr<Text> text = nullptr;
	};
}

#endif //ELEMENTOR_COMPONENTS_TEXT_BUTTON_H

//
// Created by noartem on 16.02.2024.
//

#ifndef ELEMENTOR_COMPONENTS_ICON_BUTTON_H
#define ELEMENTOR_COMPONENTS_ICON_BUTTON_H

#include "elementor.h"

#include "./Button.h"

namespace elementor::components {
	class IconButton : public Component {
	public:
		struct Props {
			std::string src;
			float size = 18.0f;
			std::optional<float> width;
			std::optional<float> height;
			std::string backgroundColor = "#ffffff";
			std::string backgroundHoverColor = "#ebf0f0";
			std::optional<std::function<EventCallbackResponse()>> onClick;
		};

		explicit IconButton(const std::shared_ptr<ApplicationContext>& ctx, const Props& props)
			: Component(ctx) {
			element = Hoverable::New(ctx, {
				.onEnter = [this, props] {
					iconBackground->setColor(props.backgroundHoverColor);
					return EventCallbackResponse::None;
				},
				.onLeave = [this, props] {
					iconBackground->setColor(props.backgroundColor);
					return EventCallbackResponse::None;
				},
				.child = Button::New(ctx, {
					.onClick = props.onClick,
					.child = Rounded::New(ctx, {
						.all = std::max(
							props.width.value_or(props.size),
							props.height.value_or(props.size)
						) / 2,
						.child = Background::New(ctx, iconBackground, {
							.color = props.backgroundColor,
							.child = Padding::New(ctx, {
								.all = 4,
								.child = Width::New(ctx, {
									.width = props.width.value_or(props.size),
									.child = Height::New(ctx, {
										.height = props.height.value_or(props.size),
										.child = SVG::New(ctx, {
											.src = props.src,
										})
									})
								})
							}),
						})
					})
				}),
			});
		}

		static std::shared_ptr<IconButton> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const Props& props
		) {
			return std::make_shared<IconButton>(ctx, props);
		}

		static std::shared_ptr<IconButton> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<IconButton>& elementRef,
			const Props& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<IconButton> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}
	private:
		std::shared_ptr<Background> iconBackground;
	};
}

#endif //ELEMENTOR_COMPONENTS_ICON_BUTTON_H

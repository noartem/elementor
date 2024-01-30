//
// Created by noartem on 03.08.2022.
//

#ifndef ELEMENTOR_COMPONENTS_FPS_LABEL_H
#define ELEMENTOR_COMPONENTS_FPS_LABEL_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
	class FPSLabel : public Component {
	public:
		explicit FPSLabel(const std::shared_ptr<ApplicationContext>& ctx)
			: Component(ctx) {
			auto labelText = Text::New(ctx, {
				.text = "FPS: ",
				.fontColor = "#000",
				.fontSize = 16.0f,
				.fontFamily = "Arial",
			});

			fpsText = Text::New(ctx, {
				.text = "0",
				.fontColor = "#000",
				.fontSize = 16,
				.fontWeight = 500,
				.fontFamily = "Fira Code",
			});

			element = Rounded::New(ctx, {
				.all = 3,
				.child = Background::New(ctx, {
					.color = "#e8e8e8cc",
					.child = Padding::New(ctx, {
						.all = 8,
						.child = Row::New(ctx, {
							.spacing = 4,
							.children = {
								labelText,
								Height::New(ctx, {
									.height = 14,
									.child = fpsText,
								})
							}
						})
					})
				})
			});

			updateFPS();
		}

		static std::shared_ptr<FPSLabel> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return std::make_shared<FPSLabel>(ctx);
		}

	private:
		std::shared_ptr<Text> fpsText;

		void updateFPS() {
			int fps = ctx->getPlatformCtx()->getPerfomance()->getFPS();
			fpsText->setText(std::to_string(fps));

			ctx->getPlatformCtx()->requestNextFrame([this]() {
				updateFPS();
			});
		}
	};
}

#endif //ELEMENTOR_COMPONENTS_FPS_LABEL_H

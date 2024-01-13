//
// Created by noartem on 15.04.2022.
//

#ifndef ELEMENTOR_BACKGROUND_H
#define ELEMENTOR_BACKGROUND_H

#include "../include.h"

namespace elementor::elements {
	struct BackgroundProps {
		const std::string_view& color = "";
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Background : public Element, public WithChild {
	public:
		explicit Background(const std::shared_ptr<ApplicationContext>& ctx) : Element(ctx), WithChild() {
		}

		Background(const std::shared_ptr<ApplicationContext>& ctx, BackgroundProps props) : Element(ctx),
																							WithChild(props.child) {
			setColor(props.color);
		}

		static std::shared_ptr<Background> New(
				const std::shared_ptr<ApplicationContext>& ctx,
				BackgroundProps props
		) {
			return std::make_shared<Background>(ctx, props);
		}

		static std::shared_ptr<Background> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		[[nodiscard]] SkColor getColor() const;

		void setColor(SkColor skColor);

		void setColor(uint8_t r, uint8_t g, uint8_t b);

		void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		void setColor(const std::string_view& hex);

		void paintBackground(SkCanvas* canvas, const ElementRect& rect) override;

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		SkColor color = SK_ColorTRANSPARENT;
	};
}


#endif //ELEMENTOR_BACKGROUND_H

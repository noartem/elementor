//
// Created by noartem on 15.04.2022.
//

#ifndef ELEMENTOR_BACKGROUND_H
#define ELEMENTOR_BACKGROUND_H

#include "../include.h"

namespace elementor::elements {
	struct BackgroundProps {
		std::optional <std::string> color;
		const std::shared_ptr <Element>& child = nullptr;
	};

	class Background : public Element, public WithChild {
	public:
		Background(const std::shared_ptr <ApplicationContext>& ctx, const BackgroundProps& props)
			: Element(ctx) {
			if (props.color.has_value()) setColor(props.color.value());
			setChild(props.child);
		}

		static std::shared_ptr <Background> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			const BackgroundProps& props
		) {
			return std::make_shared<Background>(ctx, props);
		}

		static std::shared_ptr <Background> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			std::shared_ptr <Background>& elementRef,
			const BackgroundProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr <Background> New(const std::shared_ptr <ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		[[nodiscard]] SkColor getColor() const {
			return color;
		}

		void setColor(SkColor skColor) {
			markChanged();
			color = skColor;
		}

		void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			setColor(makeSkColorFromRGBA(r, g, b, a));
		}

		void setColor(uint8_t r, uint8_t g, uint8_t b) {
			setColor(makeSkColorFromRGB(r, g, b));
		}

		void setColor(const std::string& hex) {
			setColor(makeSkColorFromHex(hex));
		}

		void setChild(const std::shared_ptr<Element>& newChild) {
			markChanged();
			child = newChild;
		}

		void paintBackground(SkCanvas* canvas, const ElementRect& rect) override;

		Size getSize(const Boundaries& boundaries) override;

		std::vector <ElementWithRect> getChildren(const ElementRect& rect) override;

		ClipBehavior getClipBehaviour() override {
			return ClipBehavior::Hard;
		}

	private:
		SkColor color = SK_ColorTRANSPARENT;
	};
}


#endif //ELEMENTOR_BACKGROUND_H

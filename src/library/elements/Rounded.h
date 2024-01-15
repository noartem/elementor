//
// Created by noartem on 21.04.2022.
//

#ifndef ELEMENTOR_ROUNDED_H
#define ELEMENTOR_ROUNDED_H

#include "../include.h"

namespace elementor::elements {
	struct RectRadius {
		float topLeft;
		float topRight;
		float bottomLeft;
		float bottomRight;
	};

	struct RoundedProps {
	public:
		std::optional<float> all;
		std::optional<float> top;
		std::optional<float> bottom;
		std::optional<float> left;
		std::optional<float> right;
		std::optional<float> topLeft;
		std::optional<float> topRight;
		std::optional<float> bottomLeft;
		std::optional<float> bottomRight;
		const std::shared_ptr<Element>& child = nullptr;

		[[nodiscard]] RectRadius getRectRadius() const {
			return {
				topLeft.value_or(left.value_or(top.value_or(all.value_or(0)))),
				topRight.value_or(right.value_or(top.value_or(all.value_or(0)))),
				bottomLeft.value_or(left.value_or(bottom.value_or(all.value_or(0)))),
				bottomRight.value_or(right.value_or(bottom.value_or(all.value_or(0))))
			};
		}
	};

	class Rounded : public Element, public WithChild {
	public:
		explicit Rounded(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx), WithChild() {
		}

		Rounded(const std::shared_ptr<ApplicationContext>& ctx, const RoundedProps& props)
			: Element(ctx),
			  WithChild(props.child) {
			rectRadius = props.getRectRadius();
		}

		static std::shared_ptr<Rounded> New(const std::shared_ptr<ApplicationContext>& ctx, const RoundedProps& props) {
			return std::make_shared<Rounded>(ctx, props);
		}

		static std::shared_ptr<Rounded> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setRadius(RectRadius newValue) {
			rectRadius = newValue;
		}

		[[nodiscard]] RectRadius getRadius() const {
			return rectRadius;
		}

		void paintBackground(SkCanvas* canvas, const ElementRect& rect) override;

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		ClipBehavior getClipBehaviour() override {
			return ClipBehavior::AntiAlias;
		}

	private:
		RectRadius rectRadius{};
	};
}


#endif //ELEMENTOR_ROUNDED_H

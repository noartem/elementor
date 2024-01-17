//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_RATIO_H
#define ELEMENTOR_RATIO_H

#include "../include.h"

namespace elementor::elements {
	struct RatioProps {
		float ratio = 0;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Ratio : public Element, public WithChild {
	public:
		explicit Ratio(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx), WithChild() {
		}

		Ratio(const std::shared_ptr<ApplicationContext>& ctx, const RatioProps& props)
			: Element(ctx),
			  WithChild(props.child) {
			setRatio(props.ratio);
		}

		static std::shared_ptr<Ratio> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const RatioProps& props
		) {
			return std::make_shared<Ratio>(ctx, props);
		}

		static std::shared_ptr<Ratio> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setRatio(float newValue) {
			ratio = newValue;
		}

		[[nodiscard]] float getRatio() const {
			return ratio;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		float ratio = 0;
	};
}


#endif //ELEMENTOR_RATIO_H

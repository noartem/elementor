//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_HEIGHT_H
#define ELEMENTOR_HEIGHT_H

#include "../include.h"

namespace elementor::elements {
	struct HeightProps {
		float height = 0;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Height : public Element, public WithChild {
	public:
		explicit Height(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx), WithChild() {
		}

		Height(const std::shared_ptr<ApplicationContext>& ctx, const HeightProps& props)
			: Element(ctx),
			  WithChild(props.child) {
			setHeight(props.height);
		}

		static std::shared_ptr<Height> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const HeightProps& props
		) {
			return std::make_shared<Height>(ctx, props);
		}

		static std::shared_ptr<Height> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setHeight(float newValue) {
			height = newValue;
		}

		[[nodiscard]] float getHeight() const {
			return height;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		float height = 0;
	};
}


#endif //ELEMENTOR_HEIGHT_H

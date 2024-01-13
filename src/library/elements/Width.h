//
// Created by noartem on 29.05.2022.
//

#ifndef ELEMENTOR_WIDTH_H
#define ELEMENTOR_WIDTH_H

#include "../include.h"

namespace elementor::elements {
	struct WidthProps {
		float width = 0;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Width : public Element, public WithChild {
	public:
		explicit Width(const std::shared_ptr<ApplicationContext>& ctx) : Element(ctx), WithChild() {
		}

		Width(const std::shared_ptr<ApplicationContext>& ctx, const WidthProps& props)
				: Element(ctx),
				  WithChild(props.child) {
			setWidth(props.width);
		}

		static std::shared_ptr<Width> New(
				const std::shared_ptr<ApplicationContext>& ctx,
				const WidthProps& props
		) {
			return std::make_shared<Width>(ctx, props);
		}

		static std::shared_ptr<Width> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setWidth(float newValue) {
			width = newValue;
		}

		[[nodiscard]] float getWidth() const {
			return width;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		float width = 0;
	};
}


#endif //ELEMENTOR_WIDTH_H

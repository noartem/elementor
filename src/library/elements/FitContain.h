//
// Created by noartem on 27.07.2022.
//

#ifndef ELEMENTOR_FIT_CONTAIN_H
#define ELEMENTOR_FIT_CONTAIN_H

#include "../include.h"

namespace elementor::elements {
	struct FitContainProps {
		const std::shared_ptr<Element>& child = nullptr;
	};

	class FitContain : public Element, public WithChild {
	public:
		explicit FitContain(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx) {
		}

		FitContain(const std::shared_ptr<ApplicationContext>& ctx, const FitContainProps& props)
			: Element(ctx),
			  WithChild(props.child) {
		}

		static std::shared_ptr<FitContain> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const FitContainProps& props
		) {
			return std::make_shared<FitContain>(ctx, props);
		}

		static std::shared_ptr<FitContain> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;
	};
}

#endif //ELEMENTOR_FIT_CONTAIN_H

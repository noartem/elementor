//
// Created by noartem on 27.07.2022.
//

#ifndef ELEMENTOR_FIT_COVER_H
#define ELEMENTOR_FIT_COVER_H

#include "../include.h"

namespace elementor::elements {
	struct FitCoverProps {
		const std::shared_ptr<Element>& child = nullptr;
	};

	class FitCover : public Element, public WithChild {
	public:
		explicit FitCover(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx) {
		}

		FitCover(const std::shared_ptr<ApplicationContext>& ctx, const FitCoverProps& props)
			: Element(ctx),
			  WithChild(props.child) {
		}

		static std::shared_ptr<FitCover> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const FitCoverProps& props
		) {
			return std::make_shared<FitCover>(ctx, props);
		}

		static std::shared_ptr<FitCover> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		ClipBehavior getClipBehaviour() override {
			return ClipBehavior::AntiAlias;
		}
	};
}

#endif //ELEMENTOR_FIT_COVER_H

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
		FitCover(const std::shared_ptr<ApplicationContext>& ctx, const FitCoverProps& props)
			: Element(ctx) {
			setChild(props.child);
		}

		static std::shared_ptr<FitCover> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const FitCoverProps& props
		) {
			return std::make_shared<FitCover>(ctx, props);
		}

		static std::shared_ptr <FitCover> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			std::shared_ptr <FitCover>& elementRef,
			const FitCoverProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<FitCover> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setChild(const std::shared_ptr <Element>& newChild) {
			markChanged();
			child = newChild;
		}

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		ClipBehavior getClipBehaviour() override {
			return ClipBehavior::AntiAlias;
		}
	};
}

#endif //ELEMENTOR_FIT_COVER_H

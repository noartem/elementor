//
// Created by noartem on 01.02.2024.
//

#ifndef ELEMENTOR_COMPONENTS_SLOT_H
#define ELEMENTOR_COMPONENTS_SLOT_H

#include "elementor.h"

namespace elementor::elements {
	struct SlotProps {
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Slot : public Element, public WithChild {
	public:
		Slot(const std::shared_ptr<ApplicationContext>& ctx, const SlotProps& props)
			: Element(ctx),
			  WithChild(props.child) {
		}

		static std::shared_ptr<Slot> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const SlotProps& props
		) {
			return std::make_shared<Slot>(ctx, props);
		}

		static std::shared_ptr<Slot> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<Slot>& elementRef,
			const SlotProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<Slot> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<WithChild>& elementRef,
			const SlotProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<Slot> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		Size getSize(const Boundaries& boundaries) override {
			if (doesNotHaveChild()) {
				return boundaries.max;
			}

			return child->getSize(boundaries);
		}

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override {
			if (doesNotHaveChild()) {
				return {};
			}

			Rect childRect = {
				.size = rect.size,
				.position = { .x = 0.0f, .y = 0.0f },
			};

			ElementWithRect childElementWithRect(child, childRect);
			return { childElementWithRect };
		}
	};
}


#endif //ELEMENTOR_COMPONENTS_SLOT_H

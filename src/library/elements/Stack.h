//
// Created by noartem on 03.02.2023.
//

#ifndef ELEMENTOR_STACK_H
#define ELEMENTOR_STACK_H

#include "../include.h"

namespace elementor::elements {
	struct StackProps {
		const std::vector<std::shared_ptr<Element>>& children = {};
	};

	class Stack : public Element, public WithChildren {
	public:
		Stack(const std::shared_ptr<ApplicationContext>& ctx, const StackProps& props)
			: Element(ctx),
			  WithChildren(props.children) {
		}

		static std::shared_ptr<Stack> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const StackProps& props
		) {
			return std::make_shared<Stack>(ctx, props);
		}

		static std::shared_ptr<Stack> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;
	};
}


#endif //ELEMENTOR_STACK_H

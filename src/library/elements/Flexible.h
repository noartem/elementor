//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_FLEXIBLE_H
#define ELEMENTOR_FLEXIBLE_H

#include "../include.h"

namespace elementor::elements {

	struct FlexibleProps {
		float grow = 1.0;
		const std::shared_ptr<Element>& child = nullptr;
	};

    class Flexible : public Element, public WithChild {
    public:
		explicit Flexible(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx), WithChild() {
		}

		Flexible(const std::shared_ptr<ApplicationContext>& ctx, const FlexibleProps& props)
			: Element(ctx),
			  WithChild(props.child) {
			setGrow(props.grow);
		}

		static std::shared_ptr<Flexible> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const FlexibleProps& props
		) {
			return std::make_shared<Flexible>(ctx, props);
		}

		static std::shared_ptr<Flexible> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

        void setGrow(float newGrow) {
			grow = newGrow;
		}

        float getGrow() const {
			return grow;
		}

        Size getSize(const Boundaries& boundaries) override;

        std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

    private:
        float grow = 1;
    };
}


#endif //ELEMENTOR_FLEXIBLE_H

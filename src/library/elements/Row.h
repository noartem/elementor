//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_ROW_H
#define ELEMENTOR_ROW_H

#include "../include.h"

namespace elementor::elements {

	struct RowProps {
		float spacing = 0;
		const std::vector <std::shared_ptr<Element>>& children = {};
	};

	class Row : public Element, public WithChildren {
	public:
		Row(const std::shared_ptr <ApplicationContext>& ctx, const RowProps& props)
			: Element(ctx) {
			setSpacing(props.spacing);
			setChildren(props.children);
		}

		static std::shared_ptr <Row> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			const RowProps& props
		) {
			return std::make_shared<Row>(ctx, props);
		}

		static std::shared_ptr <Row> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			std::shared_ptr <Row>& elementRef,
			const RowProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr <Row> New(const std::shared_ptr <ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		float getSpacing() const {
			return spacing;
		}

		void setSpacing(float newSpacing) {
			markChanged();
			spacing = newSpacing;
		}

		void setChildren(const std::vector <std::shared_ptr<Element>>& newChildren) {
			markChanged();
			children = newChildren;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector <ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		float spacing = 0;
	};
}


#endif //ELEMENTOR_ROW_H

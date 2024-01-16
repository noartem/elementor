//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_COLUMN_H
#define ELEMENTOR_COLUMN_H

#include "../include.h"

namespace elementor::elements {

	struct ColumnProps {
		float spacing = 0;
		const std::vector<std::shared_ptr<Element>>& children = {};
	};

	class Column : public Element, public WithChildren {
	public:
		Column(const std::shared_ptr<ApplicationContext>& ctx, const ColumnProps& props)
			: Element(ctx),
			  WithChildren(props.children) {
			setSpacing(props.spacing);
		}

		static std::shared_ptr<Column> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const ColumnProps& props
		) {
			return std::make_shared<Column>(ctx, props);
		}

		static std::shared_ptr<Column> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		[[nodiscard]] float getSpacing() const {
			return spacing;
		}

		void setSpacing(float newSpacing) {
			spacing = newSpacing;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		float spacing = 0;
	};
}


#endif //ELEMENTOR_COLUMN_H

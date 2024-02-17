//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_COLUMN_H
#define ELEMENTOR_COLUMN_H

#include "../include.h"

namespace elementor::elements {
	class Column : public Element, public WithChildren {
	public:
		struct Props {
			float spacing = 0;
			const std::vector <std::shared_ptr<Element>>& children = {};
		};

		Column(const std::shared_ptr <ApplicationContext>& ctx, const Props& props)
			: Element(ctx) {
			setSpacing(props.spacing);
			setChildren(props.children);
		}

		static std::shared_ptr <Column> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			const Props& props
		) {
			return std::make_shared<Column>(ctx, props);
		}

		static std::shared_ptr <Column> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			std::shared_ptr <Column>& elementRef,
			const Props& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr <Column> New(const std::shared_ptr <ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		[[nodiscard]] float getSpacing() const {
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


#endif //ELEMENTOR_COLUMN_H

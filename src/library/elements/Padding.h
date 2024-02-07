//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_PADDING_H
#define ELEMENTOR_PADDING_H

#include "../include.h"

namespace elementor::elements {
	struct PaddingsValue {
		float top = 0;
		float right = 0;
		float bottom = 0;
		float left = 0;
	};

	struct PaddingProps {
		float all = 0;
		float x = 0;
		float y = 0;
		float top = 0;
		float right = 0;
		float bottom = 0;
		float left = 0;
		const std::shared_ptr <Element>& child = nullptr;
	};

	class Padding : public Element, public WithChild {
	public:
		Padding(const std::shared_ptr <ApplicationContext>& ctx, const PaddingProps& props)
			: Element(ctx) {
			setPaddings(
				(props.top == 0) ? ((props.y == 0) ? props.all : props.y) : props.top,
				(props.right == 0) ? ((props.x == 0) ? props.all : props.x) : props.right,
				(props.bottom == 0) ? ((props.y == 0) ? props.all : props.y) : props.bottom,
				(props.left == 0) ? ((props.x == 0) ? props.all : props.x) : props.left
			);
			setChild(props.child);
		}

		static std::shared_ptr <Padding> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			const PaddingProps& props
		) {
			return std::make_shared<Padding>(ctx, props);
		}

		static std::shared_ptr <Padding> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			std::shared_ptr <Padding>& elementRef,
			const PaddingProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr <Padding> New(const std::shared_ptr <ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setPaddings(float paddingTop, float paddingRight, float paddingBottom, float paddingLeft) {
			markChanged();
			paddings = { paddingTop, paddingRight, paddingBottom, paddingLeft };
		}

		void setPaddings(float paddingTop, float paddingX, float paddingBottom) {
			this->setPaddings(paddingTop, paddingX, paddingBottom, paddingX);
		}

		void setPaddings(float paddingY, float paddingX) {
			this->setPaddings(paddingY, paddingX, paddingY, paddingX);
		}

		void setPaddings(float paddingYX) {
			this->setPaddings(paddingYX, paddingYX, paddingYX, paddingYX);
		}

		[[nodiscard]] PaddingsValue getPaddings() {
			return paddings;
		}

		void setChild(const std::shared_ptr <Element>& newChild) {
			markChanged();
			child = newChild;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector <ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		PaddingsValue paddings = { 0, 0, 0, 0 };
	};
}


#endif //ELEMENTOR_PADDING_H

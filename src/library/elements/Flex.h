//
// Created by noartem on 18.04.2022.
//

#ifndef ELEMENTOR_FLEX_H
#define ELEMENTOR_FLEX_H

#include "../include.h"

// TODO: https://css-tricks.com/snippets/css/a-guide-to-flexbox/
//   - flex-wrap
//   - row/column gap
//   - align-content

// TODO: Move to components

// TODO: Add css-grid like

namespace elementor::elements {
	enum class FlexDirection {
		Row,
		Column,
	};

	enum class FlexAlignment {
		Start,
		Center,
		End,
		Stretch,
	};

	enum class FlexCrossAlignment {
		Start,
		Center,
		End,
		SpaceBetween,
		SpaceEvenly,
	};

	struct FlexProps {
		float spacing = 0;
		FlexDirection direction = FlexDirection::Row;
		FlexAlignment alignment = FlexAlignment::Start;
		FlexCrossAlignment crossAlignment = FlexCrossAlignment::Start;
		const std::vector <std::shared_ptr<Element>>& children = {};
	};

	class Flex : public Element, public WithChildren {
	public:
		Flex(const std::shared_ptr <ApplicationContext>& ctx, const FlexProps& props)
			: Element(ctx) {
			setSpacing(props.spacing);
			setDirection(props.direction);
			setAlignment(props.alignment);
			setCrossAlignment(props.crossAlignment);
			setChildren(props.children);
		}

		static std::shared_ptr <Flex> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			const FlexProps& props
		) {
			return std::make_shared<Flex>(ctx, props);
		}

		static std::shared_ptr <Flex> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			std::shared_ptr <Flex>& elementRef,
			const FlexProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr <Flex> New(const std::shared_ptr <ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		[[nodiscard]] float getSpacing() const {
			return spacing;
		}

		void setSpacing(float newSpacing) {
			markChanged();
			spacing = newSpacing;
		}

		[[nodiscard]] FlexDirection getDirection() {
			return direction;
		}

		void setDirection(FlexDirection newDirection) {
			markChanged();
			direction = newDirection;
		}

		[[nodiscard]] FlexAlignment getAlignment() {
			return alignment;
		}

		void setAlignment(FlexAlignment newAlignment) {
			markChanged();
			alignment = newAlignment;
		}

		[[nodiscard]] FlexCrossAlignment getCrossAlignment() {
			return crossAlignment;
		}

		void setCrossAlignment(FlexCrossAlignment newAlignment) {
			markChanged();
			crossAlignment = newAlignment;
		}

		void setChildren(const std::vector <std::shared_ptr<Element>>& newChildren) {
			markChanged();
			children = newChildren;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector <ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		float spacing = 0;
		FlexDirection direction = FlexDirection::Row;
		FlexAlignment alignment = FlexAlignment::Start;
		FlexCrossAlignment crossAlignment = FlexCrossAlignment::Start;
	};

	std::shared_ptr <Flex> flex();
}


#endif //ELEMENTOR_FLEX_H

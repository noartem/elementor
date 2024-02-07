//
// Created by noartem on 14.01.2024.
//

#ifndef ELEMENTOR_ALIGN_H
#define ELEMENTOR_ALIGN_H

#include "../include.h"

namespace elementor::elements {
	struct AlignDirectionProps {
		std::optional<float> coefficient = std::nullopt;
		std::optional<float> childCoefficient = std::nullopt;
	};

	struct AlignProps {
	public:
		std::optional<float> coefficient = std::nullopt;
		std::optional<float> childCoefficient = std::nullopt;
		AlignDirectionProps width;
		AlignDirectionProps height;
		const std::shared_ptr <Element>& child = nullptr;

		[[nodiscard]] std::optional<float> getWidthCoefficient() const {
			if (width.coefficient.has_value()) return width.coefficient;
			if (coefficient.has_value()) return coefficient;
			return std::nullopt;
		}

		[[nodiscard]] std::optional<float> getWidthChildCoefficient() const {
			if (width.childCoefficient.has_value()) return width.childCoefficient;
			if (width.coefficient.has_value()) return width.coefficient;
			if (childCoefficient.has_value()) return childCoefficient;
			if (coefficient.has_value()) return coefficient;
			return std::nullopt;
		}

		[[nodiscard]] std::optional<float> getHeightCoefficient() const {
			if (height.coefficient.has_value()) return height.coefficient;
			if (coefficient.has_value()) return coefficient;
			return std::nullopt;
		}

		[[nodiscard]] std::optional<float> getHeightChildCoefficient() const {
			if (height.childCoefficient.has_value()) return height.childCoefficient;
			if (height.coefficient.has_value()) return height.coefficient;
			if (childCoefficient.has_value()) return childCoefficient;
			if (coefficient.has_value()) return coefficient;
			return std::nullopt;
		}
	};

	class Align : public Element, public WithChild {
	public:
		Align(const std::shared_ptr <ApplicationContext>& ctx, const AlignProps& props)
			: Element(ctx) {
			setWidthCoefficient(props.getWidthCoefficient(), props.getWidthChildCoefficient());
			setHeightCoefficient(props.getHeightCoefficient(), props.getHeightChildCoefficient());
			setChild(props.child);
		}

		static std::shared_ptr <Align> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			const AlignProps& props
		) {
			return std::make_shared<Align>(ctx, props);
		}

		static std::shared_ptr <Align> New(
			const std::shared_ptr <ApplicationContext>& ctx,
			std::shared_ptr <Align>& elementRef,
			const AlignProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr <Align> New(const std::shared_ptr <ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		[[nodiscard]] std::optional<float> getWidthCoefficient() const {
			return widthCoefficient;
		}

		[[nodiscard]] std::optional<float> getWidthChildCoefficient() const {
			return widthChildCoefficient;
		}

		void setWidthCoefficient(std::optional<float> newCoefficient, std::optional<float> newChildCoefficient) {
			markChanged();
			widthCoefficient = newCoefficient;
			widthChildCoefficient = newChildCoefficient;
		}

		void setWidthCoefficient(std::optional<float> newCoefficient) {
			setWidthCoefficient(newCoefficient, newCoefficient);
		}

		[[nodiscard]] std::optional<float> getHeightCoefficient() const {
			return heightCoefficient;
		}

		[[nodiscard]] std::optional<float> getHeightChildCoefficient() const {
			return heightChildCoefficient;
		}

		void setHeightCoefficient(std::optional<float> newCoefficient, std::optional<float> newChildCoefficient) {
			markChanged();
			heightCoefficient = newCoefficient;
			heightChildCoefficient = newChildCoefficient;
		}

		void setHeightCoefficient(std::optional<float> newCoefficient) {
			setHeightCoefficient(newCoefficient, newCoefficient);
		}

		void setChild(const std::shared_ptr<Element>& newChild) {
			markChanged();
			child = newChild;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector <ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		std::optional<float> widthCoefficient = std::nullopt;
		std::optional<float> widthChildCoefficient = std::nullopt;
		std::optional<float> heightCoefficient = std::nullopt;
		std::optional<float> heightChildCoefficient = std::nullopt;
	};
}

#endif //ELEMENTOR_ALIGN_H

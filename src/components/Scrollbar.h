//
// Created by noartem on 08.02.2024.
//

#ifndef ELEMENTOR_SCROLLBAR_H
#define ELEMENTOR_SCROLLBAR_H

#include "utility.h"
#include "elementor.h"

namespace elementor::elements {
	struct ScrollbarProps {
		float thickness = 0.0f;
		float spacing = 0.0f;
		const std::shared_ptr<Element>& thumb = nullptr;
		const std::shared_ptr<Scrollable>& child = nullptr;
	};

	class Scrollbar : public Element, public WithEventsHandlers {
	public:
		Scrollbar(const std::shared_ptr<ApplicationContext>& ctx, const ScrollbarProps& props)
			: Element(ctx) {
			thickness = props.thickness;
			spacing = props.spacing;
			setThumb(props.thumb);
			child = props.child;
		}

		static std::shared_ptr<Scrollbar> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const ScrollbarProps& props
		) {
			return std::make_shared<Scrollbar>(ctx, props);
		}

		static std::shared_ptr<Scrollbar> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<Scrollbar>& elementRef,
			const ScrollbarProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<Scrollbar> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		[[nodiscard]] float getThickness() const {
			return thickness;
		}

		void setThickness(float newThickness) {
			markChanged();
			thickness = newThickness;
		}

		[[nodiscard]] float getSpacing() const {
			return spacing;
		}

		void setThumb(const std::shared_ptr<Element>& newThumb);

		void setChild(const std::shared_ptr<Scrollable>& newChild) {
			markChanged();
			child = newChild;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() override;

	private:
		float thickness;
		float spacing;
		std::shared_ptr<Element> thumbX = nullptr;
		std::shared_ptr<Element> thumbY = nullptr;
		std::shared_ptr<Scrollable> child = nullptr;
		ElementRect lastRect;

		bool hovered;
	};
}

#endif //ELEMENTOR_SCROLLBAR_H

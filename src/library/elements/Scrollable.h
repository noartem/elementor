//
// Created by noartem on 22.05.2022.
//

#ifndef ELEMENTOR_SCROLLABLE_H
#define ELEMENTOR_SCROLLABLE_H

#include "../include.h"

namespace elementor::elements {
	enum class ScrollDirection {
		Vertical,
		Horizontal,
		Both,
	};

	struct ScrollableProps {
		std::optional<ScrollDirection> direction;
		std::optional<float> scrollAcceleration;
		const std::shared_ptr<elementor::Element>& child = nullptr;
	};

	class Scrollable : public Element, public WithEventsHandlers, public WithGlobalEventsHandlers, public WithChild {
	public:
		Scrollable(const std::shared_ptr<ApplicationContext>& ctx, const ScrollableProps& props)
			: Element(ctx) {
			if (props.direction.has_value()) setDirection(props.direction.value());
			if (props.scrollAcceleration.has_value()) setScrollAcceleration(props.scrollAcceleration.value());
			setChild(props.child);
		}

		// TODO: Add ELEMENT_NEW macro

		static std::shared_ptr<Scrollable> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const ScrollableProps& props
		) {
			return std::make_shared<Scrollable>(ctx, props);
		}

		static std::shared_ptr<Scrollable> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<Scrollable>& elementRef,
			const ScrollableProps& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		static std::shared_ptr<Scrollable> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setDirection(ScrollDirection newDirection) {
			markChanged();
			direction = newDirection;
		}

		[[nodiscard]] ScrollDirection getDirection() const {
			return direction;
		}

		bool isHorizontalScroll() {
			return direction != ScrollDirection::Vertical;
		}

		bool isVerticalScroll() {
			return direction != ScrollDirection::Horizontal;
		}

		[[nodiscard]] Size getSize() const {
			return lastSize;
		}

		[[nodiscard]] Size getScrollSize() const {
			return lastChildSize;
		}

		[[nodiscard]] float getMaxScrollLeft() const {
			return std::max(lastChildSize.width - lastSize.width, 0.0f);
		}

		[[nodiscard]] float getMaxScrollTop() const {
			return std::max(lastChildSize.height - lastSize.height, 0.0f);
		}

		void setScrollTop(float newScrollTop) {
			newScrollTop = std::min(std::max(newScrollTop, 0.0f), getMaxScrollTop());

			if (newScrollTop == scrollTop) {
				return;
			}

			markChanged();
			scrollTop = newScrollTop;
		}

		[[nodiscard]] float getScrollTop() const {
			return scrollTop;
		}

		void setScrollLeft(float newScrollLeft) {
			newScrollLeft = std::min(std::max(newScrollLeft, 0.0f), getMaxScrollLeft());

			if (newScrollLeft == scrollLeft) {
				return;
			}

			markChanged();
			scrollLeft = newScrollLeft;
		}

		[[nodiscard]] float getScrollLeft() const {
			return scrollLeft;
		}

		void setScrollAcceleration(float newScrollAcceleration) {
			scrollAcceleration = newScrollAcceleration;
		}

		[[nodiscard]] float getScrollAcceleration() const {
			return scrollAcceleration;
		}

		void setChild(const std::shared_ptr<Element>& newChild) {
			markChanged();
			child = newChild;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		ClipBehavior getClipBehaviour() override {
			return ClipBehavior::AntiAlias;
		}

		std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() override;

		std::vector<std::shared_ptr<EventHandler>> getGlobalEventsHandlers() override;

	private:
		ScrollDirection direction = ScrollDirection::Both;
		float scrollLeft;
		float scrollTop;
		float scrollAcceleration = 64.0;

		bool hovered;

		Size lastSize = { 0, 0 };
		Size lastChildSize = { 0, 0 };

		Size getChildSize(const Boundaries& boundaries);
	};
}


#endif //ELEMENTOR_SCROLLABLE_H

//
// Created by noartem on 26.05.2022.
//

#ifndef ELEMENTOR_SCROLLBARABLE_H
#define ELEMENTOR_SCROLLBARABLE_H

#include "../include.h"

#include "Scrollable.h"

namespace elementor::elements {
	enum class ScrollbarablePosition {
		InContent,
		OnTop,
	};

	enum class ScrollbarableVisible {
		WhenNeeded,
		Always,
	};

	struct ScrollbarableProps {
		std::optional<ScrollbarablePosition> position;
		std::optional<ScrollbarableVisible> visible;
		const std::shared_ptr<Element>& trackX = nullptr;
		const std::shared_ptr<Element>& trackY = nullptr;
		const std::shared_ptr<Element>& thumbX = nullptr;
		const std::shared_ptr<Element>& thumbY = nullptr;
		const std::shared_ptr<Scrollable>& child = nullptr;
	};

	class Scrollbar : public Element {
	public:
		Scrollbar(const std::shared_ptr<ApplicationContext>& ctx, const ScrollbarableProps& props)
			: Element(ctx) {
			if (props.position.has_value()) setPosition(props.position.value());
			if (props.visible.has_value()) setVisible(props.visible.value());
			setTrackX(props.trackX);
			setTrackY(props.trackY);
			setThumbX(props.thumbX);
			setThumbY(props.thumbY);
			setChild(props.child);
		}

		static std::shared_ptr<Scrollbar> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const ScrollbarableProps& props
		) {
			return std::make_shared<Scrollbar>(ctx, props);
		}

		static std::shared_ptr<Scrollbar> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setTrackX(const std::shared_ptr<Element>& newTrackX);

		void setTrackY(const std::shared_ptr<Element>& newTrackY);

		void setThumbX(const std::shared_ptr<Element>& thumbX);

		void setThumbY(const std::shared_ptr<Element>& thumbY);

		[[nodiscard]] ScrollbarablePosition getPosition() const {
			return position;
		}

		void setPosition(ScrollbarablePosition newPosition) {
			position = newPosition;
		}

		[[nodiscard]] ScrollbarableVisible getVisible() const {
			return visible;
		}

		void setVisible(ScrollbarableVisible newVisible) {
			visible = newVisible;
		}

		void setChild(const std::shared_ptr<Scrollable>& newChild) {
			child = newChild;
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

	private:
		ScrollbarablePosition position = ScrollbarablePosition::InContent;
		ScrollbarableVisible visible = ScrollbarableVisible::WhenNeeded;

		std::shared_ptr<Scrollable> child = nullptr;

		std::shared_ptr<Element> trackX;
		std::shared_ptr<Element> trackY;
		std::shared_ptr<Element> thumbX;
		std::shared_ptr<Element> thumbY;

		[[nodiscard]] bool showTrackX() const;

		[[nodiscard]] bool showTrackY() const;

		[[nodiscard]] Size getTrackXSize(const Boundaries& boundaries) const;

		[[nodiscard]] Size getTrackYSize(const Boundaries& boundaries) const;
	};

	void scrollbar();
}

#endif //ELEMENTOR_SCROLLBARABLE_H

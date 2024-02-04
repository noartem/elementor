//
// Created by noartem on 02.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_OUTLINE_H
#define ELEMENTOR_COMPONENTS_OUTLINE_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
	struct OutlineProps {
		BorderProps border;
		float offset = 0.0f;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Outline : public Element, public WithChild, public WithEventsHandlers {
	public:
		explicit Outline(const std::shared_ptr<ApplicationContext>& ctx, const OutlineProps& props)
			: Element(ctx),
			  WithChild(props.child) {
			offset = props.offset;
			border = Border::New(ctx, props.border);
			borderAsElement = std::dynamic_pointer_cast<Element>(border);
		}

		static std::shared_ptr<Outline> New(const std::shared_ptr<ApplicationContext>& ctx, const OutlineProps& props) {
			return std::make_shared<Outline>(ctx, props);
		}

		static std::shared_ptr<Outline> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		Size getSize(const Boundaries& boundaries) override;

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override;

		std::vector<std::shared_ptr<EventHandler>> getEventsHandlers() override;

	private:
		std::shared_ptr<Border> border = nullptr;
		std::shared_ptr<Element> borderAsElement = nullptr;

		float offset = 0.0;
		bool focused = false;

		void setFocused(bool newFocused);
	};
}

#endif //ELEMENTOR_COMPONENTS_OUTLINE_H

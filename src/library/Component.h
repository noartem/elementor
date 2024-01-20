//
// Created by noartem on 02.01.2023.
//

#ifndef ELEMENTOR_COMPONENT_H
#define ELEMENTOR_COMPONENT_H

#include <vector>
#include <vector>

#include "Render.h"
#include "Element.h"

namespace elementor::elements {
	class Component : public Element {
	public:
		explicit Component(const std::shared_ptr<ApplicationContext>& ctx)
			: Element(ctx) {
		}

		Size getSize(const Boundaries& boundaries) override {
			if (element == nullptr) {
				return boundaries.max;
			}

			return element->getSize(boundaries);
		}

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override {
			if (element == nullptr) {
				return {};
			}

			Rect elementRect = {
				.size = rect.size,
				.position = { .x =  0, .y = 0 },
			};
			ElementWithRect elementWithRect(this->element, elementRect);
			return { elementWithRect };
		}

	protected:
		std::shared_ptr<Element> element = nullptr;
	};
}

#endif //ELEMENTOR_COMPONENT_H

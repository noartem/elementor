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
		Size getSize(const Boundaries& boundaries) override {
			if (this->element) {
				return this->element->getSize(boundaries);
			}

			return boundaries.min;
		}

		void paintBackground(SkCanvas* canvas, const ElementRect& rect) override {
			this->lastRect = rect;
		}

		std::vector<ElementWithRect> getChildren(const ElementRect& rect) override {
			if (this->element) {
				ElementWithRect elementWithRect(this->element, { rect.size, { 0, 0 }});
				return { elementWithRect };
			}

			return {};
		}

	protected:
		ElementRect lastRect;
		std::shared_ptr<Element> element;
	};
}

#endif //ELEMENTOR_COMPONENT_H

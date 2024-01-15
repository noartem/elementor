//
// Created by admin on 12.01.2024.
//

#ifndef ELEMENTOR_WITH_CHILD_H
#define ELEMENTOR_WITH_CHILD_H

#include <memory>

#include "Element.h"

namespace elementor {
	class WithChild {
	public:
		explicit WithChild(const std::shared_ptr<Element>& child)
			: child(child) {
		}

		WithChild() {
		}

		void setChild(const std::shared_ptr<Element>& element) {
			this->child = element;
		}

		[[nodiscard]] std::shared_ptr<Element> getChild() const {
			return this->child;
		}

		[[nodiscard]] bool hasChild() const {
			return this->child != nullptr;
		}

		[[nodiscard]] bool doesNotHaveChild() const {
			return this->child == nullptr;
		}

		void removeChild() {
			setChild(nullptr);
		}

	protected:
		std::shared_ptr<Element> child;
	};
}

#endif //ELEMENTOR_WITH_CHILD_H

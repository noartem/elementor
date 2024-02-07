//
// Created by noartem on 12.01.2024.
//

#ifndef ELEMENTOR_WITH_CHILD_H
#define ELEMENTOR_WITH_CHILD_H

#include <memory>

#include "Element.h"

namespace elementor {
	class WithChild {
	public:
		[[nodiscard]] auto getChild() const {
			return child;
		}

		[[nodiscard]] bool hasChild() const {
			return child != nullptr;
		}

		[[nodiscard]] bool doesNotHaveChild() const {
			return child == nullptr;
		}

	protected:
		std::shared_ptr <Element> child;
	};
}

#endif //ELEMENTOR_WITH_CHILD_H

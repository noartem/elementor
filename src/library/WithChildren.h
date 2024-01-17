//
// Created by admin on 12.01.2024.
//

#ifndef ELEMENTOR_WITH_CHILDREN_H
#define ELEMENTOR_WITH_CHILDREN_H

#include <memory>
#include <vector>

#include "Element.h"

namespace elementor {
	class WithChildren {
	public:
		explicit WithChildren(const std::vector<std::shared_ptr<Element>>& children) {
			setChildren(children);
		}

		virtual void setChildren(const std::vector<std::shared_ptr<Element>>& newChildren) {
			children = newChildren;
		}

		void clearChildren() {
			setChildren({});
		}

		[[nodiscard]] std::vector<std::shared_ptr<Element>> getChildrenList() const {
			return children;
		}

		[[nodiscard]] size_t getChildrenSize() const {
			return children.size();
		}

		[[nodiscard]] std::shared_ptr<Element> getChild(int i) const {
			return children[i];
		}

		[[nodiscard]] int childIndex(const std::shared_ptr<Element>& child) const {
			for (int i = 0; i < children.size(); i++) {
				if (children[i] == child) {
					return i;
				}
			}
			return -1;
		}

	protected:
		std::vector<std::shared_ptr<Element>> children;
	};

}

#endif //ELEMENTOR_WITH_CHILDREN_H

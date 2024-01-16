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
		WithChildren(const std::vector<std::shared_ptr<Element>>& children)
			: children(children) {
		}

		void setChildren(const std::vector<std::shared_ptr<Element>>& newChildren) {
			this->children = newChildren;
		}

		void clearChildren() {
			setChildren({});
		}

		void addChild(const std::shared_ptr<Element>& child) {
			this->children.push_back(child);
		}

		void removeChild(int i) {
			if (i >= 0 && i < this->children.size()) {
				this->children.erase(this->children.begin() + i);
			}
		}

		void removeChild(const std::shared_ptr<Element>& child) {
			this->removeChild(this->childIndex(child));
		}

		[[nodiscard]] std::vector<std::shared_ptr<Element>> getChildrenList() const {
			return this->children;
		}

		[[nodiscard]] size_t getChildrenSize() const {
			return this->children.size();
		}

		[[nodiscard]] std::shared_ptr<Element> getChild(int i) const {
			return this->children[i];
		}

		[[nodiscard]] int childIndex(const std::shared_ptr<Element>& child) const {
			for (int i = 0; i < this->children.size(); i++) {
				if (this->children[i] == child) {
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

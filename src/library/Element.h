//
// Created by noartem on 13.04.2022.
//

#ifndef ELEMENTOR_ELEMENT_H
#define ELEMENTOR_ELEMENT_H

#include <utility>
#include <vector>
#include <optional>
#include <functional>

#include <include/core/SkCanvas.h>
#include <include/core/SkFontMgr.h>

#include "Render.h"
#include "ApplicationContext.h"

namespace elementor {
	enum class ClipBehavior {
		None,
		Hard,
		AntiAlias,
	};

	class Element {
	public:
		explicit Element(const std::shared_ptr<ApplicationContext>& ctx)
			: ctx(ctx) {
		}

		virtual ~Element() = default;

		virtual Size getSize(const Boundaries& boundaries) {
			return boundaries.max;
		}

		virtual void paintBackground(SkCanvas* canvas, const ElementRect& rect) {
		}

		virtual std::vector<std::tuple<const std::shared_ptr<Element>&, Rect>> getChildren(
			const ElementRect& rect
		) {
			return {};
		}

		virtual ClipBehavior getClipBehaviour() {
			return ClipBehavior::None;
		}

		virtual [[nodiscard]] bool isChanged() const {
			return changed;
		}

		virtual bool popChanged() {
			if (isChanged()) {
				changed = false;
				return true;
			} else {
				return false;
			}
		}

	protected:
		std::shared_ptr<ApplicationContext> ctx;
		bool changed = true;

		virtual void markChanged() {
			changed = true;
		}
	};

	using ElementWithRect = std::tuple<const std::shared_ptr<Element>&, Rect>;
}

#endif //ELEMENTOR_ELEMENT_H

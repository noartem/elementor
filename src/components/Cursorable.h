//
// Created by noartem on 02.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_CURSORABLE_H
#define ELEMENTOR_COMPONENTS_CURSORABLE_H

#include "utility.h"
#include "elementor.h"

namespace elementor::components {
	struct CursorableProps {
		std::optional<CursorShape> cursorShape;
		const std::shared_ptr<Element>& child = nullptr;
	};

	class Cursorable : public Component {
	public:
		explicit Cursorable(const std::shared_ptr<ApplicationContext>& ctx, const CursorableProps& props)
			: Component(ctx) {
			hoverable = Hoverable::New(ctx, {
				.onEnter = [this]() {
					this->ctx->getWindowCtx()->getCursor()->set(cursorShape);
					return EventCallbackResponse::None;
				},
				.onLeave = [this]() {
					this->ctx->getWindowCtx()->getCursor()->set(CursorShape::Default);
					return EventCallbackResponse::None;
				},
			});

			element = hoverable;

			if (props.cursorShape.has_value()) setCursorShape(props.cursorShape.value());
			setChild(props.child);
		}

		static std::shared_ptr<Cursorable> New(const std::shared_ptr<ApplicationContext>& ctx, const CursorableProps& props) {
			return std::make_shared<Cursorable>(ctx, props);
		}

		static std::shared_ptr<Cursorable> New(const std::shared_ptr<ApplicationContext>& ctx) {
			return New(ctx, {});
		}

		void setCursorShape(CursorShape newCursorShape) {
			cursorShape = newCursorShape;
		}

		[[nodiscard]] CursorShape getCursorShape() const {
			return cursorShape;
		}

		void setChild(const std::shared_ptr<Element>& child) {
			hoverable->setChild(child);
		}

	private:
		CursorShape cursorShape = CursorShape::Default;

		std::shared_ptr<Hoverable> hoverable;
	};
}

#endif //ELEMENTOR_COMPONENTS_CURSORABLE_H

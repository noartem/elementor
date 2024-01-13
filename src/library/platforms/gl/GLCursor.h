//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_CURSOR_H
#define ELEMENTOR_GL_CURSOR_H

#include "../../Element.h"

#include "GLFW/glfw3.h"

namespace elementor::platforms::gl {
	class GLCursor : public Cursor {
	public:
		GLCursor(
				const std::shared_ptr<PlatformContext>& ctx,
				GLFWwindow* window
		) : ctx(ctx), window(window) {
		}

		void set(CursorShape shape) override;

		CursorShape get() override {
			return currentShape;
		}

		Position getPosition() override {
			return position;
		}

		void setPosition(Position newValue) {
			position = newValue;
		}

	private:
		std::shared_ptr<PlatformContext> ctx;
		GLFWwindow* window;
		GLFWcursor* cursor{};
		CursorShape currentShape = CursorShape::Default;
		CursorShape appliedShape = CursorShape::Default;

		Position position{};

		void updateCursor();
	};
};

#endif //ELEMENTOR_GL_CURSOR_H

//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_CURSOR_H
#define ELEMENTOR_GL_CURSOR_H

#include "elementor.h"

#include "GLFW/glfw3.h"

#include "GLPlatformContext.h"

namespace elementor::platforms::gl {
	class GLCursor : public Cursor {
	public:
		GLCursor(GLFWwindow* window)
			: window(window) {
		}

		void set(CursorShape shape) override {
			currentShape = shape;
		}

		CursorShape get() override {
			return currentShape;
		}

		Position getPosition() override {
			return position;
		}

		void setPosition(Position newValue) {
			position = newValue;
		}

		void updateCursor() {
			if (appliedShape != currentShape) {
				auto cursor = glfwCreateStandardCursor(mapCursorShapeToInt(currentShape));
				glfwSetCursor(window, cursor);
				appliedShape = currentShape;
			}
		}

	private:
		GLFWwindow* window;

		CursorShape currentShape = CursorShape::Default;
		CursorShape appliedShape = CursorShape::Default;

		Position position = { .x = -1, .y = -1 };

		static int mapCursorShapeToInt(CursorShape shape) {
			switch (shape) {
			case CursorShape::Default:
			case CursorShape::Arrow:
				return GLFW_ARROW_CURSOR;
			case CursorShape::IBeam:
				return GLFW_IBEAM_CURSOR;
			case CursorShape::Crosshair:
				return GLFW_CROSSHAIR_CURSOR;
			case CursorShape::Hand:
				return GLFW_HAND_CURSOR;
			case CursorShape::HorizontalResize:
				return GLFW_HRESIZE_CURSOR;
			case CursorShape::VerticalResize:
				return GLFW_VRESIZE_CURSOR;
			default:
				return GLFW_ARROW_CURSOR;
			}
		}
	};
};

#endif //ELEMENTOR_GL_CURSOR_H

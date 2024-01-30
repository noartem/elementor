//
// Created by noartem on 15.08.2022.
//

#include "GLCursor.h"
#include "../../debug.h"

#include <utility>

namespace elementor::platforms::gl {
	int mapCursorShapeToInt(CursorShape shape) {
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

	void GLCursor::updateCursor() {
		if (appliedShape != currentShape) {
			auto cursor = glfwCreateStandardCursor(mapCursorShapeToInt(currentShape));
			glfwSetCursor(window, cursor);
			appliedShape = currentShape;
		}
	}

	void GLCursor::set(CursorShape shape) {
		currentShape = shape;
		ctx->requestNextFrame([this]() {
			updateCursor();
		});
	}
}


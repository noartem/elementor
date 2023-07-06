//
// Created by noartem on 15.08.2022.
//

#include "GLCursor.h"

#include <utility>

namespace elementor::platforms::gl {
    unsigned int mapCursorShapeToInt(CursorShape shape) {
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

    GLCursor::GLCursor(GLFWwindow *window, std::shared_ptr<ApplicationContext> ctx) {
        this->window = window;
        this->ctx = std::move(ctx);
    }

    void GLCursor::updateCursor() {
        if (this->appliedShape != this->currentShape) {
            this->cursor = glfwCreateStandardCursor(mapCursorShapeToInt(this->currentShape));
            glfwSetCursor(this->window, this->cursor);
            this->appliedShape = this->currentShape;
        }
    }

    void GLCursor::set(CursorShape shape) {
        this->currentShape = shape;
        this->ctx->requestNextFrame([this]() {
            this->updateCursor();
        });
    }

    CursorShape GLCursor::get() {
        return this->currentShape;
    }

    Position GLCursor::getPosition() {
        return this->position;
    }

    void GLCursor::setPosition(elementor::Position position) {
        this->position = position;
    }
}


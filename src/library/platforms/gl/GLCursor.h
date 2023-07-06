//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_GLCURSOR_H
#define ELEMENTOR_GL_GLCURSOR_H

#include "../../Element.h"

#include "GLFW/glfw3.h"

namespace elementor::platforms::gl {
    class GLCursor : public Cursor {
    public:
        GLCursor(GLFWwindow *window, std::shared_ptr<ApplicationContext> ctx);

        void set(CursorShape shape) override;

        CursorShape get() override;

        Position getPosition() override;

        void setPosition(Position position);

    private:
        std::shared_ptr<ApplicationContext> ctx;
        GLFWwindow *window;
        GLFWcursor *cursor;
        CursorShape currentShape = CursorShape::Default;
        CursorShape appliedShape = CursorShape::Default;

        Position position;

        void updateCursor();
    };
};


#endif //ELEMENTOR_GL_GLCURSOR_H

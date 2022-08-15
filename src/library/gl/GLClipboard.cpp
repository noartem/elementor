//
// Created by noartem on 15.08.2022.
//

#include "GLClipboard.h"

namespace elementor {
    void GLClipboard::set(std::string value) {
        glfwSetClipboardString(nullptr, value.c_str());
    }

    std::string GLClipboard::get() {
        return glfwGetClipboardString(nullptr);
    }
}


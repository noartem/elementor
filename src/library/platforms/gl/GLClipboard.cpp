//
// Created by noartem on 15.08.2022.
//

#include "GLClipboard.h"

namespace elementor::platforms::gl {
	void GLClipboard::set(const std::string_view& value) {
		glfwSetClipboardString(nullptr, value.data());
	}

	const std::string_view& GLClipboard::get() {
		return glfwGetClipboardString(nullptr);
	}
}


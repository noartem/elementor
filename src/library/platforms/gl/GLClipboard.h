//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_CLIPBOARD_H
#define ELEMENTOR_GL_CLIPBOARD_H

#include "elementor.h"

#include "GLFW/glfw3.h"

namespace elementor::platforms::gl {
	class GLClipboard : public Clipboard {
	public:
		void set(const std::string_view& value) override {
			glfwSetClipboardString(nullptr, value.data());
		}

		const std::string_view& get() override {
			return glfwGetClipboardString(nullptr);
		}
	};
};


#endif //ELEMENTOR_GL_CLIPBOARD_H

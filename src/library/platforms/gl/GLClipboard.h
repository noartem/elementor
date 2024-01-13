//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_CLIPBOARD_H
#define ELEMENTOR_GL_CLIPBOARD_H

#include "../../Element.h"

#include "GLFW/glfw3.h"

namespace elementor::platforms::gl {
	class GLClipboard : public Clipboard {
	public:
		void set(const std::string_view& value) override;

		const std::string_view& get() override;
	};
};


#endif //ELEMENTOR_GL_CLIPBOARD_H

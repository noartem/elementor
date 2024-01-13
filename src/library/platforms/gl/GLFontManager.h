//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_FONT_MANAGER_H
#define ELEMENTOR_GL_FONT_MANAGER_H

#include "../../Element.h"

#include <modules/skparagraph/include/TypefaceFontProvider.h>

namespace elementor::platforms::gl {
	class GLFontManager {
	public:
		GLFontManager();

		sk_sp<SkFontMgr> getSkFontManager();

		void registerFontFromSkData(sk_sp<SkData> data);

		void registerFontFromPath(const std::string& path);

	private:
		sk_sp<skia::textlayout::TypefaceFontProvider> skFontManager;
	};
};


#endif //ELEMENTOR_GL_FONT_MANAGER_H

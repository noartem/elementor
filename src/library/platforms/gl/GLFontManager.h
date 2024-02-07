//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_FONT_MANAGER_H
#define ELEMENTOR_GL_FONT_MANAGER_H

#include "elementor.h"

#include <modules/skparagraph/include/TypefaceFontProvider.h>

namespace elementor::platforms::gl {
	class GLFontManager {
	public:
		GLFontManager() {
			skFontManager = sk_make_sp<skia::textlayout::TypefaceFontProvider>();
		}

		[[nodiscard]] sk_sp<SkFontMgr> getSkFontManager() const {
			return skFontManager;
		}

		void registerFontFromSkData(sk_sp<SkData> data) {
			skFontManager->registerTypeface(SkTypeface::MakeFromData(std::move(data)));
		}

		void registerFontFromPath(const std::string& path) {
			registerFontFromSkData(SkData::MakeFromFileName(path.c_str()));
		}

	private:
		sk_sp<skia::textlayout::TypefaceFontProvider> skFontManager;
	};
};


#endif //ELEMENTOR_GL_FONT_MANAGER_H

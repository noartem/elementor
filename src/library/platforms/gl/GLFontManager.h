//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_GLFONTMANAGER_H
#define ELEMENTOR_GL_GLFONTMANAGER_H

#include "../../Element.h"

#include <modules/skparagraph/include/TypefaceFontProvider.h>

namespace sktextlayout = skia::textlayout;

namespace elementor {
    class GLFontManager {
    public:
        GLFontManager();

        sk_sp<SkFontMgr> getSkFontManager();

        void registerFontFromSkData(sk_sp<SkData> data);

        void registerFontFromPath(const std::string& path);

    private:
        sk_sp<sktextlayout::TypefaceFontProvider> skFontManager;
    };
};


#endif //ELEMENTOR_GL_GLFONTMANAGER_H

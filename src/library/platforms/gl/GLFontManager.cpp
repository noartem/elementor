//
// Created by noartem on 15.08.2022.
//

#include "GLFontManager.h"

#include <utility>

namespace elementor {
    GLFontManager::GLFontManager() {
        this->skFontManager = sk_make_sp<sktextlayout::TypefaceFontProvider>();
    }

    sk_sp<SkFontMgr> GLFontManager::getSkFontManager() {
        return this->skFontManager;
    }

    void GLFontManager::registerFontFromSkData(sk_sp<SkData> data) {
        this->skFontManager->registerTypeface(SkTypeface::MakeFromData(std::move(data)));
    }

    void GLFontManager::registerFontFromPath(const std::string &path) {
        this->registerFontFromSkData(SkData::MakeFromFileName(path.c_str()));
    }
}


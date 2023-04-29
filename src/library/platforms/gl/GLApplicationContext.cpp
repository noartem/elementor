//
// Created by noartem on 15.08.2022.
//

#include "GLApplicationContext.h"

#include <utility>

namespace elementor::platforms::gl {
    GLApplicationContext::GLApplicationContext(std::shared_ptr<GLPlatform> platform) {
        this->platform = std::move(platform);
    }

    float GLApplicationContext::getPixelScale() {
        return this->platform->getPixelScale();
    }

    void GLApplicationContext::setPixelScale(float scale) {
        return this->platform->setPixelScale(scale);
    }

    std::string GLApplicationContext::getLocale() {
        return this->platform->getLocale();
    }

    void GLApplicationContext::setLocale(std::string locale) {
        return this->platform->setLocale(locale);
    }

    std::shared_ptr<Clipboard> GLApplicationContext::getClipboard() {
        return this->platform->getClipboard();
    }

    std::shared_ptr<Perfomance> GLApplicationContext::getPerfomance() {
        return this->platform->getPerfomance();
    }

    sk_sp<SkFontMgr> GLApplicationContext::getSkFontManager() {
        return this->platform->getSkFontManager();
    }

    void GLApplicationContext::requestNextFrame(std::function<void()> callback) {
        this->platform->requestNextFrame(callback);
    }

    std::shared_ptr<Window> GLApplicationContext::makeWindow(Size size) {
        return this->platform->makeWindow(size);
    }
}


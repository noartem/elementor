//
// Created by noartem on 15.08.2022.
//

#include "GLApplicationContext.h"

namespace elementor {
    GLApplicationContext::GLApplicationContext(GLApplication *application) {
        this->application = application;
    }

    Clipboard *GLApplicationContext::getClipboard() {
        return this->application->getClipboard();
    }

    Perfomance *GLApplicationContext::getPerfomance() {
        return this->application->getPerfomance();
    }

    sk_sp<SkFontMgr> GLApplicationContext::getSkFontManager() {
        return this->application->getSkFontManager();
    }

    void GLApplicationContext::requestNextFrame(std::function<void ()> callback) {
        this->application->requestNextFrame(callback);
    }
}


//
// Created by noartem on 06.08.2022.
//

#include "GLApplication.h"

namespace elementor {
    std::unique_ptr<GLApplication> glApplication() {
        return std::make_unique<GLApplication>();
    }

    GLApplication::GLApplication() {
        this->platform = new GLPlatform();
        this->platform->application = new Application();
    }

    GLApplication *GLApplication::setTitle(std::string title) {
        this->platform->title = title;
        return this;
    }

    GLApplication *GLApplication::setDefaultSize(Size const& size) {
        this->platform->size = size;
        return this;
    }

    GLApplication *GLApplication::setMinSize(Size const& size) {
        this->platform->minSize = size;
        return this;
    }

    GLApplication *GLApplication::setMaxSize(Size const& size) {
        this->platform->maxSize = size;
        return this;
    }

    GLApplication *GLApplication::setRoot(Element *root) {
        this->platform->application->root = root;
        return this;
    }

    GLApplication *GLApplication::registerFontFromPath(std::string path) {
        this->platform->getFontManager()->registerFontFromPath(path);
        return this;
    }

    int GLApplication::run() {
        return this->platform->run();
    }
}

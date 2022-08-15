//
// Created by noartem on 14.04.2022.
//

#ifndef ELEMENTOR_GL_GLPLATFORM_H
#define ELEMENTOR_GL_GLPLATFORM_H

#include "../../Element.h"

#include "GLClipboard.h"
#include "GLFontManager.h"
#include "GLPerfomance.h"
#include "GLWindow.h"

namespace elementor {
    class GLPlatform {
    public:
        GLPlatform();

        GLWindow *makeWindow();

        void run();
        void requestNextFrame(std::function<void ()> callback);

        GLClipboard *getClipboard();
        GLPerfomance *getPerfomance();
        GLFontManager *getFontManager();
        sk_sp<SkFontMgr> getSkFontManager();

    private:
        GLClipboard *clipboard;
        GLFontManager *fontManager;
        GLPerfomance *perfomance;

        ApplicationContext *applicationContext;

        std::vector<GLWindow *> windows;

        std::vector<std::function<void ()>> rnfNextQueue;
        std::vector<std::function<void ()>> rnfCurrentQueue;
        void applyRnfQueue();
    };
};

#endif //ELEMENTOR_GL_GLPLATFORM_H

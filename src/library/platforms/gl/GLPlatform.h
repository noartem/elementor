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

        ~GLPlatform();

        GLWindow *makeWindow(Size size);
        void addWindow(GLWindow *window);
        void removeWindow(GLWindow *window);
        void removeWindow(unsigned int index);

        void run();
        void requestNextFrame(const std::function<void ()>& callback);

        GLClipboard *getClipboard();
        GLPerfomance *getPerfomance();
        GLFontManager *getFontManager();
        sk_sp<SkFontMgr> getSkFontManager();

        float getPixelScale();
        void setPixelScale(float scale);

        std::string getLocale();
        void setLocale(std::string locale);

    private:
        GLClipboard *clipboard;
        GLFontManager *fontManager;
        GLPerfomance *perfomance;

        ApplicationContext *applicationContext;

        std::vector<GLWindow *> windows;

        std::vector<std::function<void ()>> rnfNextQueue;
        std::vector<std::function<void ()>> rnfCurrentQueue;
        void applyRnfQueue();

        float pixelScale;
        float calcPixelScale();

        std::string locale = "en";
    };
};

#endif //ELEMENTOR_GL_GLPLATFORM_H

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

        std::shared_ptr<GLWindow> makeWindow(Size size);

        void addWindow(const std::shared_ptr<GLWindow>& window);

        void removeWindow(const std::shared_ptr<GLWindow>& window);

        void removeWindow(unsigned int index);

        void run();

        void requestNextFrame(const std::function<void()> &callback);

        std::shared_ptr<GLClipboard> getClipboard();

        std::shared_ptr<GLPerfomance> getPerfomance();

        std::shared_ptr<GLFontManager> getFontManager();

        sk_sp<SkFontMgr> getSkFontManager();

        float getPixelScale() const;

        void setPixelScale(float scale);

        std::string getLocale();

        void setLocale(std::string newLocale);

    private:
        std::shared_ptr<GLClipboard> clipboard;
        std::shared_ptr<GLFontManager> fontManager;
        std::shared_ptr<GLPerfomance> perfomance;

        std::shared_ptr<ApplicationContext> applicationContext;

        std::vector<std::shared_ptr<GLWindow>> windows;

        std::vector<std::function<void()>> rnfNextQueue;
        std::vector<std::function<void()>> rnfCurrentQueue;

        void applyRnfQueue();

        float pixelScale;

        static float calcPixelScale();

        std::string locale = "en";
    };
};

#endif //ELEMENTOR_GL_GLPLATFORM_H

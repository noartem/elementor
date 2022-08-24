//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_GLAPPLICATIONCONTEXT_H
#define ELEMENTOR_GL_GLAPPLICATIONCONTEXT_H

#include "../../Element.h"
#include "GLPlatform.h"

namespace elementor {
    class GLApplicationContext : public ApplicationContext {
    public:
        GLApplicationContext(GLPlatform *platform);

        float getPixelScale() override;
        void setPixelScale(float scale) override;

        std::string getLocale() override;
        void setLocale(std::string locale) override;

        Clipboard *getClipboard() override;
        Perfomance *getPerfomance() override;
        sk_sp<SkFontMgr> getSkFontManager() override;

        void requestNextFrame(std::function<void ()> callback) override;

        Window *makeWindow() override;

    private:
        GLPlatform *platform;
    };
};


#endif //ELEMENTOR_GL_GLAPPLICATIONCONTEXT_H

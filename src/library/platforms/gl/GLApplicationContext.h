//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_GLAPPLICATIONCONTEXT_H
#define ELEMENTOR_GL_GLAPPLICATIONCONTEXT_H

#include "../../Element.h"
#include "GLPlatform.h"

namespace elementor::platforms::gl {
    class GLApplicationContext : public ApplicationContext {
    public:
        explicit GLApplicationContext(std::shared_ptr<GLPlatform> platform);

        explicit GLApplicationContext(GLPlatform *platform) : GLApplicationContext(
                std::shared_ptr<GLPlatform>(platform)) {};

        float getPixelScale() override;

        void setPixelScale(float scale) override;

        std::string getLocale() override;

        void setLocale(std::string locale) override;

        std::shared_ptr<Clipboard> getClipboard() override;

        std::shared_ptr<Perfomance> getPerfomance() override;

        sk_sp<SkFontMgr> getSkFontManager() override;

        void requestNextFrame(std::function<void()> callback) override;

        std::shared_ptr<Window> makeWindow(Size size) override;

    private:
        std::shared_ptr<GLPlatform> platform;
    };
};


#endif //ELEMENTOR_GL_GLAPPLICATIONCONTEXT_H

//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_GLAPPLICATIONCONTEXT_H
#define ELEMENTOR_GL_GLAPPLICATIONCONTEXT_H

#include "../Element.h"
#include "GLApplication.h"

namespace elementor {
    class GLApplicationContext : public ApplicationContext {
    public:
        GLApplicationContext(GLApplication *application);

        Clipboard *getClipboard() override;
        Perfomance *getPerfomance() override;
        sk_sp<SkFontMgr> getSkFontManager() override;
        void requestNextFrame(std::function<void ()> callback) override;

    private:
        GLApplication *application;
    };
};


#endif //ELEMENTOR_GL_GLAPPLICATIONCONTEXT_H

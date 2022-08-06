//
// Created by noartem on 06.08.2022.
//

#ifndef ELEMENTOR_GLAPPLICATION_H
#define ELEMENTOR_GLAPPLICATION_H

#include "GLPlatform.h"
#include <memory>

namespace elementor {
    class GLApplication {
    public:
        GLApplication();

        GLApplication *setTitle(std::string title);
        GLApplication *setDefaultSize(Size const& size);
        GLApplication *setMinSize(Size const& size);
        GLApplication *setMaxSize(Size const& size);
        GLApplication *setRoot(Element *root);
        GLApplication *registerFontFromPath(std::string path);

        int run();

    private:
        GLPlatform *platform;
    };

    std::unique_ptr<GLApplication> glApplication();
};


#endif //ELEMENTOR_GLAPPLICATION_H

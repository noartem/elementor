//
// Created by noartem on 15.08.2022.
//

#ifndef ELEMENTOR_GL_GLCLIPBOARD_H
#define ELEMENTOR_GL_GLCLIPBOARD_H

#include "../Element.h"

#include "GLFW/glfw3.h"

namespace elementor {    
    class GLClipboard : public Clipboard {
    public:
        void set(std::string value) override;
        std::string get() override;
    };
};


#endif //ELEMENTOR_GL_GLCLIPBOARD_H

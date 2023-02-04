//
// Created by noartem on 04.02.2023.
//

#include "utility.h"

namespace elementor::components {
    void openURL(std::string url) {
#if defined(OS_HOST_WINDOWS)
        std::string command = "start " + url;
#elif defined(OS_HOST_LINUX)
        std::string command = "xdg-open " + url;
#elif defined(OS_HOST_MACOS)
        std::string command = "open " + url;
#endif

        system(command.c_str());
    }
}

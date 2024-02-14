//
// Created by noartem on 13.01.2024.
//

#ifndef ELEMENTOR_DEBUG_H
#define ELEMENTOR_DEBUG_H

#include <iostream>

#ifndef PRINT
#define PRINT(x) std::cout << #x"=" << x << std::endl
#endif

#ifndef LOG
#define LOG(x) std::cout << x << std::endl
#endif

#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

#ifndef D_PRINT
#define D_PRINT(x) D(PRINT(x))
#endif

#ifndef D_LOG
#define D_LOG(x) D(LOG(x))
#endif

#endif //ELEMENTOR_DEBUG_H

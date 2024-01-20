//
// Created by admin on 13.01.2024.
//

#ifndef ELEMENTOR_DEBUG_H
#define ELEMENTOR_DEBUG_H

#include <iostream>

#ifndef E_PRINT
#define E_PRINT(x) std::cout << #x"=" << x << std::endl
#endif

#ifndef E_LOG
#define E_LOG(x) std::cout << x << std::endl
#endif

#endif //ELEMENTOR_DEBUG_H

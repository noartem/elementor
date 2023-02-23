//
// Created by noartem on 04.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_UTILITY_H
#define ELEMENTOR_COMPONENTS_UTILITY_H

#include <string>
#include <time.h>

namespace elementor::components {
    void openURL(std::string url);

    tm now_tm();

    std::string leftPadAndFit(const std::string &value, unsigned  int size, const char paddingChar);

    int daysInMonth(int month, int year);
}

#endif //ELEMENTOR_COMPONENTS_UTILITY_H

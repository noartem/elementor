//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_ENTRY_H
#define DIARY_ENTRY_H

#include <chrono>
#include <string>

struct Entry {
    std::tm datetime;
    int duration;
    std::string place;
};

#endif //DIARY_ENTRY_H

//
// Created by noartem on 29.06.2022.
//

#ifndef DIARY_DIARY_ENTRY_H
#define DIARY_DIARY_ENTRY_H

#include <chrono>
#include <string>

std::tm parseDate(std::string value);

class DiaryEntry {
public:
    DiaryEntry(std::tm datetime, float duration, std::string place);

    DiaryEntry(std::string datetime, float duration, std::string place);

    std::tm getDatetime();

    std::string getDatetimeFormatted();

    float getDuration();

    std::string getPlace();

    std::string toString();

    operator std::string();

private:
    std::tm datetime;
    float duration;
    std::string place;
};

#endif //DIARY_DIARY_ENTRY_H

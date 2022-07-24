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
    DiaryEntry(std::tm datetime, float duration, std::u32string place);

    DiaryEntry(std::u32string datetime, float duration, std::u32string place);

    std::tm getDatetime();

    std::u32string getDatetimeFormatted();

    float getDuration();

    std::u32string getDurationFormatted();

    std::u32string getPlace();

private:
    std::tm datetime;
    float duration;
    std::u32string place;
};

#endif //DIARY_DIARY_ENTRY_H

//
// Created by noartem on 29.06.2022.
//

#include "DiaryEntry.h"
#include "utility.h"

#include <iomanip>
#include <sstream> // DO NOT REMOVE, REQUIRED FOR WINDOWS BUILD

#define TIME_FORMAT "%Y-%m-%d %H:%M"

extern "C" char* strptime(const char* s, const char* f, struct tm* tm) {
  std::istringstream input(s);
  input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
  input >> std::get_time(tm, f);
  if (input.fail()) {
    return NULL;
  } else {
    return (char*)(s + input.tellg());
  }
}

std::u32string floatToU32String(float value) {
    std::string text = std::to_string(value);
    std::u32string textU32;
    fromUTF8(text, textU32);
    return textU32;
}

std::tm parseDate(std::u32string value) {
    std::tm tm = {};
    strptime(toUTF8(value).c_str(), TIME_FORMAT, &tm);
    return tm;
}

DiaryEntry::DiaryEntry(std::tm datetime, float duration, std::u32string place) {
    this->datetime = datetime;
    this->duration = duration;
    this->place = place;
}

DiaryEntry::DiaryEntry(std::u32string datetime, float duration, std::u32string place) {
    this->datetime = parseDate(datetime);
    this->duration = duration;
    this->place = place;
}

std::tm DiaryEntry::getDatetime() {
    return this->datetime;
}

std::u32string DiaryEntry::getDatetimeFormatted() {
    char datetimeFormattedRaw[32];
    std::strftime(datetimeFormattedRaw, 32, TIME_FORMAT, &this->datetime);
    std::string datetimeFormatted = datetimeFormattedRaw;
    std::u32string datetimeFormattedU32;
    fromUTF8(datetimeFormatted, datetimeFormattedU32);
    return datetimeFormattedU32;
}

std::u32string DiaryEntry::getDurationFormatted() {
    return floatToU32String(this->duration);
}

float DiaryEntry::getDuration() {
    return this->duration;
}

std::u32string DiaryEntry::getPlace() {
    return this->place;
}

//
// Created by noartem on 29.06.2022.
//

#include "DiaryEntry.h"

#include <fmt/format.h>

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

std::tm parseDate(std::string value) {
    std::tm tm = {};
    strptime(value.c_str(), TIME_FORMAT, &tm);
    return tm;
}

DiaryEntry::DiaryEntry(std::tm datetime, float duration, std::string place) {
    this->datetime = datetime;
    this->duration = duration;
    this->place = place;
}

DiaryEntry::DiaryEntry(std::string datetime, float duration, std::string place) {
    this->datetime = parseDate(datetime);
    this->duration = duration;
    this->place = place;
}

std::tm DiaryEntry::getDatetime() {
    return this->datetime;
}

std::string DiaryEntry::getDatetimeFormatted() {
    char datetimeFormatted[32];
    std::strftime(datetimeFormatted, 32, TIME_FORMAT, &this->datetime);
    return datetimeFormatted;
}

std::string DiaryEntry::getDurationFormatted() {
    return fmt::format("{}", this->duration);
}

float DiaryEntry::getDuration() {
    return this->duration;
}

std::string DiaryEntry::getPlace() {
    return this->place;
}

std::string DiaryEntry::toString() {
    return fmt::format("DateTime = {}, Duration = {}, Place = {}.", this->getDatetimeFormatted(), this->duration, this->place);
}

DiaryEntry::operator std::string() {
    return this->toString();
}

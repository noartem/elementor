//
// Created by noartem on 27.06.2022.
//

#include "DiaryService.h"
#include "DiaryEntry.h"
#include "utility.h"

#include "csv.h"

#include <chrono>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdint.h>

std::vector<DiaryEntry *> readEntriesFromFile(std::string path) {
    std::vector<DiaryEntry *> entries;
    io::CSVReader<3> in(path);
    in.read_header(io::ignore_extra_column, "datetime", "duration", "place");
    std::string datetime; float duration; std::string place;
    while(in.read_row(datetime, duration, place)){
        std::u32string datetimeU32;
        fromUTF8(datetime, datetimeU32);
        std::u32string placeU32;
        fromUTF8(place, placeU32);
        DiaryEntry *entry = new DiaryEntry(datetimeU32, duration, placeU32);
        entries.push_back(entry);
    }
    return entries;
}

void saveEntriesToFile(std::string path, std::vector<DiaryEntry *> entries) {
    std::ofstream o;
    o.open(path);
    o << "datetime,duration,place\n";
    for (DiaryEntry *entry : entries) {
        std::u32string datetime = entry->getDatetimeFormatted();
        o << toUTF8(datetime) << ",";
        std::u32string duration = entry->getDurationFormatted();
        o << toUTF8(duration) << ",";
        std::u32string place = entry->getPlace();
        o << toUTF8(place) << "\n";
    }
    o.close();
}

std::vector<DiaryEntry *> DiaryService::findAll() {
    return this->entries;
}

void DiaryService::add(DiaryEntry *entry) {
    if (entry == NULL) {
        return;
    }

    std::tm entryTime = entry->getDatetime();
    time_t entryTimeT = std::mktime(&entryTime);
    auto i = std::upper_bound(this->entries.begin(), this->entries.end(), entryTimeT, [](time_t value, DiaryEntry *otherEntry) {
        std::tm otherEntryTime = otherEntry->getDatetime();
        time_t otherEntryTimeT = std::mktime(&otherEntryTime);
        return value < otherEntryTimeT;
    });
    this->entries.insert(i, entry);
}

void DiaryService::add(std::vector<DiaryEntry *> entries) {
    for (DiaryEntry *entry : entries) {
        this->add(entry);
    }
}

void DiaryService::remove(unsigned int index) {
    if (index < this->entries.size()) {
        this->entries.erase(this->entries.begin() + index);
    }
}

void DiaryService::remove(DiaryEntry *entry) {
    for (unsigned int i = 0; i < this->entries.size(); ++i) {
        if (this->entries[i] == entry) {
            this->remove(i);
            return;
        }
    }
}

std::vector<DiaryEntry *> DiaryService::findWhereDatetimeBetween(std::tm start, std::tm end) {
    std::time_t startT = std::mktime(&start);
    std::time_t endT = std::mktime(&end);

    std::vector<DiaryEntry *> result;
    for (DiaryEntry *entry : this->entries) {
        std::tm entryDateTime = entry->getDatetime();
        std::time_t entryDateTimeT = std::mktime(&entryDateTime);
        if (entryDateTimeT > startT && entryDateTimeT < endT) {
            result.push_back(entry);
        }
    }

    return result;
}
//
// Created by noartem on 27.06.2022.
//

#include "DiaryService.h"
#include "DiaryEntry.h"

#include "csv.h"

#include <chrono>
#include <vector>
#include <string>
#include <iostream>

std::vector<DiaryEntry *> readEntriesFromFile(std::string filename) {
    std::vector<DiaryEntry *> entries;
    io::CSVReader<3> in(filename);
    in.read_header(io::ignore_extra_column, "datetime", "duration", "place");
    std::string datetime; float duration; std::string place;
    while(in.read_row(datetime, duration, place)){
        DiaryEntry *entry = new DiaryEntry(datetime, duration, place);
        entries.push_back(entry);
    }
    return entries;
}

DiaryService *DiaryService::MakeFromFile(std::string filename) {
    DiaryService *service = new DiaryService();
    service->entries = readEntriesFromFile(filename);
    return service;
}

void DiaryService::log() {
    std::cout << "Diary: " << std::endl;
    for(DiaryEntry *entry : this->entries) {
        std::cout << "\t* " << entry->toString() << std::endl;
    }
}

std::vector<DiaryEntry *> DiaryService::findAll() {
    return this->entries;
}

void DiaryService::add(DiaryEntry *entry) {
    this->entries.push_back(entry);
}

bool DiaryService::remove(unsigned int index) {
    if (this->entries.size() < index) {
        this->entries.erase(this->entries.begin() + index);
        return true;
    } else {
        return false;
    }
}

bool DiaryService::replace(DiaryEntry *entry, unsigned int index) {
    if (this->entries.size() < index) {
        this->entries[index] = entry;
        return true;
    } else {
        return false;
    }
}

DiaryEntry *DiaryService::findWhereDatetime(std::tm datetime) {
    std::time_t datetimeT = std::mktime(&datetime);
    for (DiaryEntry *entry : this->entries) {
        std::tm entryDateTime = entry->getDatetime();
        std::time_t entryDateTimeT = std::mktime(&entryDateTime);
        if (entryDateTimeT == datetimeT) {
            return entry;
        }
    }
}

DiaryEntry *DiaryService::findWhereDatetime(std::string datetime) {
    return this->findWhereDatetime(parseDate(datetime));
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

std::vector<DiaryEntry *> DiaryService::findWhereDatetimeBetween(std::string start, std::string end) {
    return this->findWhereDatetimeBetween(parseDate(start), parseDate(end));
}
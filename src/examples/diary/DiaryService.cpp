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
#include <fstream>
#include <stdint.h>

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

void DiaryService::log() {
    std::cout << "Diary: " << std::endl;
    for(DiaryEntry *entry : this->entries) {
        std::cout << "\t* " << entry->toString() << std::endl;
    }
}

void DiaryService::sort() {
    std::sort(this->entries.begin(), this->entries.end(), [] (DiaryEntry *a, DiaryEntry *b) {
        std::tm aTime = a->getDatetime();
        std::tm bTime = b->getDatetime();
        return std::mktime(&aTime) < std::mktime(&bTime);
    });
}

void DiaryService::saveToFile(std::string filename) {
    this->sort();
    std::ofstream o;
    o.open(filename);
    o << "datetime,duration,place\n";
    for (DiaryEntry *entry : this->entries) {
        o << entry->getDatetimeFormatted() << ",";
        o << entry->getDurationFormatted() << ",";
        o << entry->getPlace() << "\n";
    }
    o.close();
}

std::vector<DiaryEntry *> DiaryService::findAll() {
    return this->entries;
}

void DiaryService::add(DiaryEntry *entry) {
    this->entries.push_back(entry);
}

void DiaryService::add(std::vector<DiaryEntry *> entries) {
    for (DiaryEntry *entry : entries) {
        this->add(entry);
    }
    this->sort();
}

void DiaryService::remove(unsigned int index) {
    this->entries.erase(this->entries.begin() + index);
}

void DiaryService::remove(DiaryEntry *entry) {
    for (unsigned int i = 0; i < this->entries.size(); ++i) {
        if (this->entries[i] == entry) {
            this->remove(i);
            return;
        }
    }
}

void DiaryService::replace(DiaryEntry *entry, unsigned int index) {
    this->entries[index] = entry;
}

void DiaryService::replace(DiaryEntry *oldEntry, DiaryEntry *newEntry) {
    for (unsigned int i = 0; i < this->entries.size(); ++i) {
        if (this->entries[i] == oldEntry) {
            this->replace(newEntry, i);
            return;
        }
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
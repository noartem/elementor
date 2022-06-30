//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_DIARY_SERVICE_H
#define DIARY_DIARY_SERVICE_H

#include "DiaryEntry.h"

#include <vector>

std::vector<DiaryEntry *> readEntriesFromFile(std::string filename);

class DiaryService {
public:
    static DiaryService *MakeFromFile(std::string filename);

    void log();

    void add(DiaryEntry *entry);

    bool remove(unsigned int index);

    bool replace(DiaryEntry *entry, unsigned int index);

    std::vector<DiaryEntry *> findAll();

    DiaryEntry *findWhereDatetime(std::tm datetime);

    DiaryEntry *findWhereDatetime(std::string datetime);

    std::vector<DiaryEntry *> findWhereDatetimeBetween(std::tm start, std::tm end);

    std::vector<DiaryEntry *> findWhereDatetimeBetween(std::string start, std::string end);

private:
    std::vector<DiaryEntry *> entries;
};

#endif //DIARY_DIARY_SERVICE_H

//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_DIARY_SERVICE_H
#define DIARY_DIARY_SERVICE_H

#include "DiaryEntry.h"

#include <vector>

std::vector<DiaryEntry *> readEntriesFromFile(std::string path);

void saveEntriesToFile(std::string path, std::vector<DiaryEntry *>);

class DiaryService {
public:
    void add(DiaryEntry *entry);

    void add(std::vector<DiaryEntry *> entries);

    void remove(unsigned int index);

    void remove(DiaryEntry *entry);

    std::vector<DiaryEntry *> findAll();

    std::vector<DiaryEntry *> findWhereDatetimeBetween(std::tm start, std::tm end);

private:
    std::vector<DiaryEntry *> entries;
};

#endif //DIARY_DIARY_SERVICE_H

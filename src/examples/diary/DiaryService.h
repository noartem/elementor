//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_DIARY_SERVICE_H
#define DIARY_DIARY_SERVICE_H

#include "DiaryEntry.h"

#include <vector>
#include <memory>

std::vector<std::shared_ptr<DiaryEntry>> readEntriesFromFile(std::string path);

void saveEntriesToFile(std::string path, std::vector<std::shared_ptr<DiaryEntry>>);

class DiaryService {
public:
    void add(std::shared_ptr<DiaryEntry> entry);

    void add(std::vector<std::shared_ptr<DiaryEntry>> entries);

    void remove(unsigned int index);

    void remove(std::shared_ptr<DiaryEntry> entry);

    std::vector<std::shared_ptr<DiaryEntry>> findAll();

    std::vector<std::shared_ptr<DiaryEntry>> findWhereDatetimeBetween(std::tm start, std::tm end);

private:
    std::vector<std::shared_ptr<DiaryEntry>> entries;
};

#endif //DIARY_DIARY_SERVICE_H

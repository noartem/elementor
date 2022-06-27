//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_DIARY_SERVICE_H
#define DIARY_DIARY_SERVICE_H

#include "Entry.h"

#include <vector>

class DiaryService {
public:
    DiaryService();

    void log();

    std::vector<Entry> getEntries();

private:
    std::vector<Entry> entries;
};

#endif //DIARY_DIARY_SERVICE_H

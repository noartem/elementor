//
// Created by noartem on 27.06.2022.
//

#include "DiaryService.h"

#include "rapidcsv.h"

#include <vector>
#include <string>
#include <time.h>
#include <chrono>

#define TIME_FORMAT "%Y-%m-%d %H:%M"

DiaryService::DiaryService() {
    rapidcsv::Document doc("diary.csv", rapidcsv::LabelParams(-1, -1));
    int rowCount = doc.GetRowCount();
    for (int i = 1; i < rowCount; i++) {
        std::vector<std::string> row = doc.GetRow<std::string>(i);

        std::tm datetime = {};
        strptime(row[0].c_str(), TIME_FORMAT, &datetime);

        this->entries.push_back(Entry{datetime, std::stoi(row[1]), row[2]});
    }
}

void DiaryService::log() {
    std::cout << "DiaryService" << std::endl;
    for(Entry entry : this->entries) {
        char datetime[100];
        std::strftime(datetime, 100, TIME_FORMAT, &entry.datetime);

        std::cout << "date: " << datetime << ", duration: " << entry.duration << " (hours), place: " << entry.place << std::endl;
    }
}

std::vector<Entry> DiaryService::getEntries() {
    return this->entries;
}

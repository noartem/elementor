//
// Created by noartem on 30.06.2022.
//

#include "PageTomorrowEntries.h"
#include "DiaryEntryElement.h"
#include "Scroll.h"

PageTomorrowEntries::PageTomorrowEntries(DiaryService *service) {
    this->service = service;
}

std::string PageTomorrowEntries::getName() {
    return "Tomorrow Entries";
}

std::string PageTomorrowEntries::getDescription() {
    return "Displays entries attached to tomorrow";
}

Element *PageTomorrowEntries::getScene() {
    Column *entriesColumn = column()
        ->setSpacing(12);

    std::time_t tNow = std::time(0) + 6*1000;
    std::tm *now = std::localtime(&tNow);
    std::tm tomorrowStart = {0, 0, 0, now->tm_mday+1, now->tm_mon, now->tm_year};
    std::tm tomorrowEnd = {59, 59, 23, now->tm_mday+1, now->tm_mon, now->tm_year};

    for (DiaryEntry *entry : this->service->findWhereDatetimeBetween(tomorrowStart, tomorrowEnd)) {
        entriesColumn
            ->appendChild(alignWidth()
                ->setChild(diaryEntryElement(entry)));
    }

    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(entriesColumn));
}

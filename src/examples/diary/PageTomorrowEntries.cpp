//
// Created by noartem on 30.06.2022.
//

#include "PageTomorrowEntries.h"
#include "PageEntry.h"
#include "DiaryEntryElement.h"

PageTomorrowEntries::PageTomorrowEntries(DiaryService *service, PAGE_CHANGER pageChanger) {
    this->service = service;
    this->pageChanger = pageChanger;
}

std::string PageTomorrowEntries::getName() {
    return "Tomorrow Entries";
}

std::shared_ptr<Element> PageTomorrowEntries::makeElement() {
    std::shared_ptr<Column> entriesColumn = column()
        ->setSpacing(12);

    std::time_t tNow = std::time(0) + 6*1000;
    std::tm *now = std::localtime(&tNow);
    std::tm tomorrowStart = {0, 0, 0, now->tm_mday+1, now->tm_mon, now->tm_year};
    std::tm tomorrowEnd = {59, 59, 23, now->tm_mday+1, now->tm_mon, now->tm_year};

    for (DiaryEntry *entry : this->service->findWhereDatetimeBetween(tomorrowStart, tomorrowEnd)) {
        entriesColumn
            ->appendChild(alignWidth()
                ->setChild(clickable()
                    ->setChild(diaryEntryElement(entry))
                    ->onClick([this, entry] () { this->pageChanger(new PageEntry(this->service, entry, this, this->pageChanger)); })));
    }

    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(32)
                ->appendChild(text()
                    ->setFontColor("#2B1615")
                    ->setFontFamily("Times New Roman")
                    ->setFontSize(24)
                    ->setText("Tomorrow entries"))
                ->appendChild(entriesColumn)));
}

//
// Created by noartem on 30.06.2022.
//

#include "PageTodayEntries.h"
#include "PageEntry.h"
#include "DiaryEntryElement.h"
#include "Scroll.h"

PageTodayEntries::PageTodayEntries(DiaryService *service) {
    this->service = service;
}

std::string PageTodayEntries::getName() {
    return "Today Entries";
}

void PageTodayEntries::setPageChanger(PAGE_CHANGER pageChanger) {
    this->pageChanger = pageChanger;
}

std::tm *now() {
    std::time_t t = std::time(0);
    return std::localtime(&t);
}

Element *PageTodayEntries::getScene() {
    Column *entriesColumn = column()
        ->setSpacing(12);

    std::time_t tNow = std::time(0) + 6*1000;
    std::tm *now = std::localtime(&tNow);
    std::tm todayStart = {0, 0, 0, now->tm_mday, now->tm_mon, now->tm_year};
    std::tm todayEnd = {59, 59, 23, now->tm_mday, now->tm_mon, now->tm_year};

    for (DiaryEntry *entry : this->service->findWhereDatetimeBetween(todayStart, todayEnd)) {
        entriesColumn
            ->appendChild(alignWidth()
                ->setChild(clickable()
                    ->setChild(diaryEntryElement(entry))
                    ->onClick([this, entry] () {
                        this->pageChanger(new PageEntry(this->service, entry, this));
                    })));
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
                    ->setText("Today entries"))
                ->appendChild(entriesColumn)));
}

//
// Created by noartem on 30.06.2022.
//

#include "PageTodayEntries.h"
#include "PageEntry.h"
#include "DiaryEntryElement.h"

PageTodayEntries::PageTodayEntries(std::shared_ptr<DiaryService> service, PAGE_CHANGER pageChanger) {
    this->service = service;
    this->pageChanger = pageChanger;
}

std::string PageTodayEntries::getName() {
    return "Today Entries";
}

std::tm *now() {
    std::time_t t = std::time(0);
    return std::localtime(&t);
}

std::shared_ptr<Element> PageTodayEntries::makeElement() {
    std::shared_ptr<Column> entriesColumn = column()
        ->setSpacing(12);

    std::time_t tNow = std::time(0) + 6*1000;
    std::tm *now = std::localtime(&tNow);
    std::tm todayStart = {0, 0, 0, now->tm_mday, now->tm_mon, now->tm_year};
    std::tm todayEnd = {59, 59, 23, now->tm_mday, now->tm_mon, now->tm_year};

    for (std::shared_ptr<DiaryEntry> entry : this->service->findWhereDatetimeBetween(todayStart, todayEnd)) {
        entriesColumn
            ->appendChild(alignWidth()
                ->setChild(clickable()
                    ->setChild(diaryEntryElement(entry))
                    ->onClick([this, entry] () { this->pageChanger(std::make_shared<PageEntry>(this->service, entry, shared_from_this(), this->pageChanger)); })));
    }

    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(32)
                ->appendChild(height()
                    ->setHeight(17.6)
                    ->setChild(text()
                        ->setFontColor("#2B1615")
                        ->setFontFamily("Times New Roman")
                        ->setFontSize(24)
                        ->setText("Today entries")))
                ->appendChild(entriesColumn)));
}

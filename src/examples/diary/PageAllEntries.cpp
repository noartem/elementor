//
// Created by noartem on 27.06.2022.
//

#include "PageAllEntries.h"
#include "PageEntry.h"
#include "DiaryEntryElement.h"

PageAllEntries::PageAllEntries(std::shared_ptr<DiaryService> service, PAGE_CHANGER pageChanger) {
    this->service = service;
    this->pageChanger = pageChanger;
}

std::string PageAllEntries::getName() {
    return "All Entries";
}

std::shared_ptr<Element> PageAllEntries::makeElement() {
    std::shared_ptr<Column> entriesColumn = column()
        ->setSpacing(12);

    for (std::shared_ptr<DiaryEntry> entry : this->service->findAll()) {
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
                ->appendChild(text()
                    ->setFontColor("#2B1615")
                    ->setFontFamily("Times New Roman")
                    ->setFontSize(24)
                    ->setText("All entries"))
                ->appendChild(entriesColumn)));
}

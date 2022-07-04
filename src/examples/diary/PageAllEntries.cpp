//
// Created by noartem on 27.06.2022.
//

#include "PageAllEntries.h"
#include "PageEntry.h"
#include "DiaryEntryElement.h"
#include "Scroll.h"

PageAllEntries::PageAllEntries(DiaryService *service) {
    this->service = service;
}

std::string PageAllEntries::getName() {
    return "All Entries";
}

std::string PageAllEntries::getDescription() {
    return "Displays all entries from diary";
}

void PageAllEntries::setPageChanger(PAGE_CHANGER pageChanger) {
    this->pageChanger = pageChanger;
}

Element *PageAllEntries::getScene() {
    Column *entriesColumn = column()
        ->setSpacing(12);

    for (DiaryEntry *entry : this->service->findAll()) {
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
            ->setChild(entriesColumn));
}

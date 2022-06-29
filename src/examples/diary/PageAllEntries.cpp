//
// Created by noartem on 27.06.2022.
//

#include "PageAllEntries.h"
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

Element *PageAllEntries::getScene() {
    Column *entriesColumn = column()
        ->setSpacing(12);

    for (DiaryEntry *entry : this->service->findAll()) {
        entriesColumn
            ->appendChild(text()
                ->setFontColor("#2B1615")
                ->setFontFamily("Times New Roman")
                ->setFontSize(18)
                ->setText(entry->toString()));
    }

    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(entriesColumn));
}

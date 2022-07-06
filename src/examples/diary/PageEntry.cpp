//
// Created by noartem on 04.07.2022.
//

#include "PageEntry.h"

PageEntry::PageEntry(DiaryService *service, DiaryEntry *entry, Page *backPage, PAGE_CHANGER pageChanger) {
    this->service = service;
    this->entry = entry;
    this->backPage = backPage;
    this->pageChanger = pageChanger;

    this->inputDatetime = textInput()
        ->setValue(entry->getDatetimeFormatted());
    this->inputDuration = textInput()
        ->setValue(entry->getDurationFormatted());
    this->inputPlace = textInput()
        ->setValue(entry->getPlace());
}

std::string PageEntry::getName() {
    return "Entry";
}

void PageEntry::saveEntry() {
    std::string datetime = this->inputDatetime->getValue();
    float duration = std::stof(this->inputDuration->getValue());
    std::string place = this->inputPlace->getValue();
    this->service->replace(this->entry, new DiaryEntry(datetime, duration, place));
    this->pageChanger(this->backPage);
}

void PageEntry::deleteEntry() {
    this->service->remove(this->entry);
    this->pageChanger(this->backPage);
}

Element *PageEntry::makeElement() {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->appendChild(padding()
                    ->setPaddings(0, 0, 32, 0)
                    ->setChild(text()
                        ->setFontColor("#2B1615")
                        ->setFontFamily("Times New Roman")
                        ->setFontSize(24)
                        ->setText("Entry")))
                ->appendChild(padding()
                    ->setPaddings(12, 16)
                    ->setChild(column()
                        ->setSpacing(8)
                        ->appendChild(row()
                            ->setSpacing(16)
                            ->appendChild(text()
                                ->setFontColor("#2B1615")
                                ->setFontSize(18)
                                ->setText("Date and time"))
                            ->appendChild(text()
                                ->setFontColor("#675C5B")
                                ->setFontSize(18)
                                ->setText("In format \"YYYY-mm-dd HH:MM\"")))
                        ->appendChild(expandedWidth()
                            ->setChild(this->inputDatetime))))
                ->appendChild(padding()
                    ->setPaddings(12, 16)
                    ->setChild(column()
                        ->setSpacing(8)
                        ->appendChild(text()
                            ->setFontColor("#2B1615")
                            ->setFontSize(18)
                            ->setText("Duration"))
                        ->appendChild(expandedWidth()
                            ->setChild(this->inputDuration))))
                ->appendChild(padding()
                    ->setPaddings(12, 16)
                    ->setChild(column()
                        ->setSpacing(8)
                        ->appendChild(text()
                            ->setFontColor("#2B1615")
                            ->setFontSize(18)
                            ->setText("Place"))
                        ->appendChild(expandedWidth()
                            ->setChild(this->inputPlace))))
                ->appendChild(padding()
                    ->setPaddings(12, 16)
                    ->setChild(row()
                        ->setSpacing(8)
                        ->appendChild(clickable()
                            ->onClick([this] () { this->saveEntry(); })
                            ->setChild(rounded()
                                ->setRadius(6)
                                ->setChild(background()
                                    ->setColor("#BEE8FA")
                                    ->setChild(padding()
                                        ->setPaddings(12, 18, 12, 16)
                                        ->setChild(text()
                                            ->setFontColor("#001E28")
                                            ->setFontSize(18)
                                            ->setText("Save"))))))
                        ->appendChild(clickable()
                            ->onClick([this] () { this->deleteEntry(); })
                            ->setChild(rounded()
                                ->setRadius(6)
                                ->setChild(background()
                                    ->setColor("#980214")
                                    ->setChild(padding()
                                    ->setPaddings(12, 16)
                                        ->setChild(text()
                                        ->setFontColor("#FFFFFF")
                                            ->setFontSize(18)
                                            ->setText("Delete"))))))))));
}

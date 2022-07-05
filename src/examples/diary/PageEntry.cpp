//
// Created by noartem on 04.07.2022.
//

#include "PageEntry.h"
#include "TextInput.h"

PageEntry::PageEntry(DiaryService *service, DiaryEntry *entry, Page *backPage) {
    this->service = service;
    this->entry = entry;
    this->backPage = backPage;

    this->datetime = entry->getDatetimeFormatted();
    this->duration = entry->getDurationFormatted();
    this->place = entry->getPlace();
}

std::string PageEntry::getName() {
    return "Entry";
}

void PageEntry::setPageChanger(PAGE_CHANGER pageChanger) {
    this->pageChanger = pageChanger;
}

void PageEntry::saveEntry() {
    this->service->replace(this->entry, new DiaryEntry(this->datetime, std::stof(this->duration), this->place));
    this->service->saveToFile(this->filename);
    this->pageChanger(this->backPage);
}

void PageEntry::deleteEntry() {
    this->service->remove(this->entry);
    this->service->saveToFile(this->filename);
    this->pageChanger(this->backPage);
}

Element *PageEntry::getScene() {
    return padding()
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
                        ->setChild(textInput()
                            ->setValue(this->entry->getDatetimeFormatted())
                            ->onChange([this] (std::string text) {
                                this->datetime = text;
                                return text;
                            })))))
            ->appendChild(padding()
                ->setPaddings(12, 16)
                ->setChild(column()
                    ->setSpacing(8)
                    ->appendChild(text()
                        ->setFontColor("#2B1615")
                        ->setFontSize(18)
                        ->setText("Duration"))
                    ->appendChild(expandedWidth()
                        ->setChild(textInput()
                            ->setValue(this->entry->getDurationFormatted())
                            ->onChange([this] (std::string text) {
                                this->duration = text;
                                return text;
                            })))))
            ->appendChild(padding()
                ->setPaddings(12, 16)
                ->setChild(column()
                    ->setSpacing(8)
                    ->appendChild(text()
                        ->setFontColor("#2B1615")
                        ->setFontSize(18)
                        ->setText("Place"))
                    ->appendChild(expandedWidth()
                        ->setChild(textInput()
                            ->setValue(this->entry->getPlace())
                            ->onChange([this] (std::string text) {
                                this->place = text;
                                return text;
                            })))))
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
                                        ->setText("Delete")))))))));
}

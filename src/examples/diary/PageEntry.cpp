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

std::string PageEntry::getDescription() {
    return "Diary Entry at " + this->entry->getDatetimeFormatted();
}

void PageEntry::setPageChanger(PAGE_CHANGER pageChanger) {
    this->pageChanger = pageChanger;
}

void PageEntry::saveEntry() {
    this->service->replace(this->entry, new DiaryEntry(this->datetime, std::stof(this->duration), this->place));
    this->service->save();
    this->pageChanger(this->backPage);
}

void PageEntry::deleteEntry() {
    this->service->remove(this->entry);
    this->service->save();
    this->pageChanger(this->backPage);
}

Element *PageEntry::getScene() {
    return padding()
        ->setPaddings(24, 36)
        ->setChild(column()
            ->appendChild(padding()
                ->setPaddings(12, 16)
                ->setChild(column()
                    ->setSpacing(8)
                    ->appendChild(text()
                        ->setFontColor("#2B1615")
                        ->setFontSize(16)
                        ->setText("Date and time"))
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
                        ->setFontSize(16)
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
                        ->setFontSize(16)
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
                                        ->setFontSize(16)
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
                                        ->setFontSize(16)
                                        ->setText("Delete")))))))));
}

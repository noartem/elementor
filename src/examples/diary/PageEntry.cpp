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
        ->setValue(entry == NULL ? U"2022-07-07 08:00" : entry->getDatetimeFormatted());
    this->inputDuration = textInput()
        ->setValue(entry == NULL ? U"1" : entry->getDurationFormatted());
    this->inputPlace = textInput()
        ->setValue(entry == NULL ? U"" : entry->getPlace());
}

std::string PageEntry::getName() {
    return "Entry";
}

void PageEntry::saveEntry() {
    std::u32string datetime = this->inputDatetime->getValue();
    std::u32string durationU32 = this->inputDuration->getValue();
    float duration = std::stof(toUTF8(durationU32));
    std::u32string place = this->inputPlace->getValue();
    DiaryEntry *newEntry = new DiaryEntry(datetime, duration, place);
    if (this->entry != NULL) {
        this->service->remove(this->entry);
    }
    this->service->add(newEntry);
    this->pageChanger(this->backPage);
}

void PageEntry::deleteEntry() {
    this->service->remove(this->entry);
    this->pageChanger(this->backPage);
}

Element *PageEntry::makeDatetimeField() {
    return column()
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
            ->setChild(this->inputDatetime));
}

Element *PageEntry::makeDurationField() {
    return column()
        ->setSpacing(8)
        ->appendChild(text()
            ->setFontColor("#2B1615")
            ->setFontSize(18)
            ->setText("Duration"))
        ->appendChild(expandedWidth()
            ->setChild(this->inputDuration));
}

Element *PageEntry::makePlaceField() {
    return column()
        ->setSpacing(8)
        ->appendChild(text()
            ->setFontColor("#2B1615")
            ->setFontSize(18)
            ->setText("Place"))
        ->appendChild(expandedWidth()
            ->setChild(this->inputPlace));
}

Element *PageEntry::makeForm() {
    return column()
        ->setSpacing(12)
        ->appendChild(this->makeDatetimeField())
        ->appendChild(this->makeDurationField())
        ->appendChild(this->makePlaceField());
}

Element *PageEntry::makeSaveControl() {
    return clickable()
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
                        ->setText("Save")))));
}

Element *PageEntry::makeDeleteControl() {
    return clickable()
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
                        ->setText("Delete")))));
}

Element *PageEntry::makeControls() {
    Row *controls = row()
        ->setSpacing(8);

    controls->appendChild(this->makeSaveControl());

    if (this->entry != NULL) {
        controls->appendChild(this->makeDeleteControl());
    }

    return controls;
}

Element *PageEntry::makeElement() {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(24)
                ->appendChild(height()
                    ->setHeight(17.6)
                    ->setChild(text()
                        ->setFontColor("#2B1615")
                        ->setFontFamily("Times New Roman")
                        ->setFontSize(24)
                        ->setText("Entry")))
                ->appendChild(empty())
                ->appendChild(this->makeForm())
                ->appendChild(this->makeControls())));
}

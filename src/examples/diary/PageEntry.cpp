//
// Created by noartem on 04.07.2022.
//

#include "PageEntry.h"

#include <iostream>

PageEntry::PageEntry(const std::shared_ptr<DiaryService>& service, const std::shared_ptr<DiaryEntry>& entry, const std::shared_ptr<Page>& backPage, const PAGE_CHANGER& pageChanger) {
    this->service = service;
    this->entry = entry;
    this->backPage = backPage;
    this->pageChanger = pageChanger;
}

std::string PageEntry::getName() {
    return "Entry";
}

void PageEntry::saveEntry() {
    float duration = std::stof(toUTF8(this->duration));
    auto newEntry = std::make_shared<DiaryEntry>(this->datetime, duration, this->place);
    if (this->entry != nullptr) {
        this->service->remove(this->entry);
    }
    this->service->add(newEntry);
    this->pageChanger(this->backPage);
}

void PageEntry::deleteEntry() {
    this->service->remove(this->entry);
    this->pageChanger(this->backPage);
}

std::shared_ptr<Element> PageEntry::makeDatetimeField() {
    auto thisPointer = shared_from_this();
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
            ->setChild(textInput()
                ->onChange([thisPointer] (std::u32string newValue) {
                    thisPointer->datetime = newValue;
                    return newValue;
                })
                ->setValue(entry == nullptr
                    ? U"2022-07-07 08:00"
                    : entry->getDatetimeFormatted())));
}

std::shared_ptr<Element> PageEntry::makeDurationField() {
    auto thisPointer = shared_from_this();
    return column()
        ->setSpacing(8)
        ->appendChild(text()
            ->setFontColor("#2B1615")
            ->setFontSize(18)
            ->setText("Duration"))
        ->appendChild(expandedWidth()
            ->setChild(textInput()
                ->onChange([thisPointer] (std::u32string newValue) {
                    thisPointer->duration = newValue;
                    return newValue;
                })
                ->setValue(entry == nullptr
                    ? U"1"
                    : entry->getDurationFormatted())));
}

std::shared_ptr<Element> PageEntry::makePlaceField() {
    auto thisPointer = shared_from_this();
    return column()
        ->setSpacing(8)
        ->appendChild(text()
            ->setFontColor("#2B1615")
            ->setFontSize(18)
            ->setText("Place"))
        ->appendChild(expandedWidth()
            ->setChild(textInput()
                ->onChange([thisPointer] (std::u32string newValue) {
                    thisPointer->place = newValue;
                    return newValue;
                })
                ->setValue(entry == nullptr
                    ? U""
                    : entry->getPlace())));
}

std::shared_ptr<Element> PageEntry::makeForm() {
    return column()
        ->setSpacing(12)
        ->appendChild(this->makeDatetimeField())
        ->appendChild(this->makeDurationField())
        ->appendChild(this->makePlaceField());
}

std::shared_ptr<Element> PageEntry::makeSaveControl() {
    return clickable()
        ->onClick([this] () {
            this->saveEntry();
        })
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

std::shared_ptr<Element> PageEntry::makeDeleteControl() {
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

std::shared_ptr<Element> PageEntry::makeControls() {
    std::shared_ptr<Row> controls = row()
        ->setSpacing(8);

    controls->appendChild(this->makeSaveControl());

    if (this->entry != nullptr) {
        controls->appendChild(this->makeDeleteControl());
    }

    return controls;
}

std::shared_ptr<Element> PageEntry::makeElement() {
    auto thisPage = shared_from_this();

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

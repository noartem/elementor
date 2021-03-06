//
// Created by noartem on 04.07.2022.
//

#ifndef DIARY_PAGE_ENTRY_H
#define DIARY_PAGE_ENTRY_H

#include "utility.h"
#include "Page.h"
#include "DiaryService.h"

class PageEntry: public Page {
public:
    PageEntry(DiaryService *service, DiaryEntry *entry, Page *backPage, PAGE_CHANGER pageChanger);

    std::string getName() override;

    Element *makeElement() override;

private:
    DiaryService *service;
    DiaryEntry *entry;
    PAGE_CHANGER pageChanger;
    Page *backPage;
    TextInput *inputDatetime;
    TextInput *inputDuration;
    TextInput *inputPlace;

    void saveEntry();

    void deleteEntry();

    Element *makeDatetimeField();

    Element *makeDurationField();

    Element *makePlaceField();

    Element *makeForm();

    Element *makeSaveControl();

    Element *makeDeleteControl();

    Element *makeControls();
};


#endif //DIARY_PAGE_ENTRY_H

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
    PageEntry(DiaryService *service, DiaryEntry *entry, Page *homePage);

    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;

    void setPageChanger(PAGE_CHANGER pageChanger);

private:
    DiaryService *service;
    DiaryEntry *entry;
    PAGE_CHANGER pageChanger;
    Page *backPage;
    std::string datetime;
    std::string duration;
    std::string place;

    void saveEntry();

    void deleteEntry();
};


#endif //DIARY_PAGE_ENTRY_H

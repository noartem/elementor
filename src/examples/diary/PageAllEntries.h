//
// Created by noartem on 27.06.2022.
//

#ifndef DIARY_PAGE_ALL_ENTRIES_H
#define DIARY_PAGE_ALL_ENTRIES_H

#include "utility.h"
#include "Page.h"
#include "DiaryService.h"

class PageAllEntries: public Page {
public:
    PageAllEntries(DiaryService *service);

    std::string getName() override;

    Element *getScene() override;

    void setPageChanger(PAGE_CHANGER pageChanger);

private:
    DiaryService *service;
    PAGE_CHANGER pageChanger;
};


#endif //DIARY_PAGE_ALL_ENTRIES_H

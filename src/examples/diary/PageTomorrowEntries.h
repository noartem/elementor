//
// Created by noartem on 30.06.2022.
//

#ifndef DIARY_PAGE_TOMORROW_ENTRIES_H
#define DIARY_PAGE_TOMORROW_ENTRIES_H

#include "utility.h"
#include "Page.h"
#include "DiaryService.h"

class PageTomorrowEntries: public Page {
public:
    PageTomorrowEntries(DiaryService *service);

    std::string getName() override;

    Element *getScene() override;

    void setPageChanger(PAGE_CHANGER pageChanger);

private:
    DiaryService *service;
    PAGE_CHANGER pageChanger;
};


#endif //DIARY_PAGE_TOMORROW_ENTRIES_H

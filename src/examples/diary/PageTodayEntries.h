//
// Created by noartem on 30.06.2022.
//

#ifndef DIARY_PAGE_TODAY_ENTRIES_H
#define DIARY_PAGE_TODAY_ENTRIES_H

#include "utility.h"
#include "Page.h"
#include "DiaryService.h"

class PageTodayEntries: public Page {
public:
    PageTodayEntries(DiaryService *service);

    std::string getName() override;

    std::string getDescription() override;

    Element *getScene() override;

    void setPageChanger(PAGE_CHANGER pageChanger);

private:
    DiaryService *service;
    PAGE_CHANGER pageChanger;
};


#endif //DIARY_PAGE_TODAY_ENTRIES_H

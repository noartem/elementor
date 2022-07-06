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
    PageTodayEntries(DiaryService *service, PAGE_CHANGER pageChanger);

    std::string getName() override;

    Element *makeElement() override;

private:
    DiaryService *service;
    PAGE_CHANGER pageChanger;
};


#endif //DIARY_PAGE_TODAY_ENTRIES_H

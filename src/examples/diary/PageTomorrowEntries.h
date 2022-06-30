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

    std::string getDescription() override;

    Element *getScene() override;

private:
    DiaryService *service;
};


#endif //DIARY_PAGE_TOMORROW_ENTRIES_H
